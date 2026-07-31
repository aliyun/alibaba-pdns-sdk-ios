/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
//  当前版本：2.3.1

#import <Foundation/Foundation.h>
#import "DNSDomainInfo.h"

typedef NS_OPTIONS(NSUInteger, DNSResolverScheme) {
    DNSResolverSchemeHttp     = 0,
    DNSResolverSchemeHttps    = 1 << 0
};

@interface DNSResolver : NSObject

/// 唯一初始化方法
+ (instancetype)share;

//控制台注册生成，必传参数，该参数设置已被弃用，替换为- (void)setAccountId:(NSString *)accountId andAccessKeyId:(NSString *)accessKeyId andAccesskeySecret:(NSString *)accesskeySecret;方法设置
@property (nonatomic, strong) NSString *accountId __attribute__((unavailable("该参数设置已被弃用，替换为- (void)setAccountId:(NSString *)accountId andAccessKeyId:(NSString *)accessKeyId andAccesskeySecret:(NSString *)accesskeySecret")));

//控制台生成鉴权参数，必传参数，该参数设置已被弃用，替换为- (void)setAccountId:(NSString *)accountId andAccessKeyId:(NSString *)accessKeyId andAccesskeySecret:(NSString *)accesskeySecret;方法设置
@property (nonatomic, strong) NSString *accessKeyId __attribute__((unavailable("该参数设置已被弃用，替换为- (void)setAccountId:(NSString *)accountId andAccessKeyId:(NSString *)accessKeyId andAccesskeySecret:(NSString *)accesskeySecret")));

//控制台生成鉴权参数，必传参数，该参数设置已被弃用，替换为- (void)setAccountId:(NSString *)accountId andAccessKeyId:(NSString *)accessKeyId andAccesskeySecret:(NSString *)accesskeySecret;方法设置
@property (nonatomic, strong) NSString *accesskeySecret __attribute__((unavailable("该参数设置已被弃用，替换为- (void)setAccountId:(NSString *)accountId andAccessKeyId:(NSString *)accessKeyId andAccesskeySecret:(NSString *)accesskeySecret")));

///是否开启缓存， 默认为YES
@property (nonatomic, assign) BOOL cacheEnable;

//是否区分不同网络下的缓存数据， 默认为YES
@property (nonatomic, assign) BOOL ispEnable;

//是否开启IP测速， 2.3.1版本起默认为YES，之前默认为NO
@property (nonatomic, assign) BOOL speedTestEnable;

///设置测速方式,0为（icmp探测），不为0例如：80/443,（socket端口建连探测）   2.3.1版本起默认80，之前默认443
@property (nonatomic, assign) int speedPort;

///IPv6测速让分(ms)：开启测速的v4/v6混合排序中，IPv6有效测速时间减去该值，v4/v6相差不超过该值时优先IPv6。默认0=关闭，有效范围[0,1000]，仅测速开启时生效
@property (nonatomic, assign) NSInteger speedTestIpv6PreferMs;

///是否只获取域名对应的ip， 默认为NO
@property (nonatomic, assign) BOOL shortEnable;

///是否使用ipv6网络解析域名，默认为NO
@property (nonatomic, assign) BOOL ipv6Enable;

///最大的否定缓存ttl配置，默认30s
@property (nonatomic, assign) double maxNegativeCache;

///最小的缓存ttl配置，默认60s
@property (nonatomic, assign) double minCacheTTL;

///最大的缓存ttl配置，默认3600s
@property (nonatomic, assign) double maxCacheTTL;

///DNS scheme 类型， 默认为：DNSResolverSchemeHttps
@property (nonatomic, assign) DNSResolverScheme scheme;

///域名解析缓存最大数量，默认为100个域名
@property (nonatomic, assign) NSInteger cacheCountLimit;

///解析超时时间，建议2~5s，默认3s
@property (nonatomic, assign) NSTimeInterval timeout;

///缓存永久有效， 默认为NO
@property (nonatomic, assign) BOOL immutableCacheEnable;

///是否开启localdns兜底， 默认为YES
@property (nonatomic, assign) BOOL localdnsEnable;

///设置ecs地址
@property (nonatomic, copy) NSString *ednsSubnet;

///SDK同时在飞的解析请求最大并发数
///取值范围[1, 50]，越界自动夹紧；默认10，推荐范围[5, 30]
///建议在首次解析请求之前设置
@property (nonatomic, assign) NSInteger maxConcurrentResolveCount;

+ (void)enableLog;

+ (void)disableLog;
//获取SessionId
- (NSString *)getSessionId;

/**
 * 设置公共 DNS 鉴权信息
 * 通过此接口公共 DNS 鉴权凭证
 * SDK 将使用这些信息发起请求
 * @param accountId 控制台注册生成 accountId（用于鉴权）
 * @param accessKeyId 控制台注册生成accessKeyId（用于鉴权）
 * @param accesskeySecret 控制台注册生成accesskeySecret（用于鉴权）
 */
- (void)setAccountId:(NSString *_Nonnull)accountId andAccessKeyId:(NSString *_Nonnull)accessKeyId andAccesskeySecret:(NSString *_Nonnull)accesskeySecret;

/**使用私有化部署的融合DNS相关，若只使用公共DNS不需要设置该方法
 *
 * 设置融合 DNS 服务器地址和鉴权信息
 * 客户通过此接口传入私有 DNS 服务器的地址和鉴权凭证
 * SDK 将使用这些信息发起请求
 * @param ipv4 IPv4 地址数组（可为 nil）
 * @param ipv6 IPv6 地址数组（可为 nil）
 * @param host Host 域名数组（可为 nil）
 * @param port 服务端口（如 @"443"，传 nil 使用默认）
 * @param healthCheckDomain 熔断后健康检查域名，当某个解析服务连续失败次数大于3次后，会触发熔断，该解析服务ip会进入healthCheck状态
 *       （后续请求不会走该服务），定时器每分钟会使用该healthCheckDomain调用解析接口探测该解析服务是否可以使用，如果探测成功，则恢复alive状态（后续请求可以走该服务）
 * @param accessKeyId 客户私有 accessKeyId（用于鉴权）
 * @param accesskeySecret 客户私有 accesskeySecret（用于鉴权）
 */
- (void)setFusionDNSWithIPv4:(NSArray<NSString *> * _Nullable)ipv4
                        IPv6:(NSArray<NSString *> * _Nullable)ipv6
                        Host:(NSArray<NSString *> * _Nullable)host
                        Port:(NSString * _Nullable)port
           HealthCheckDomain:(NSString * _Nonnull)healthCheckDomain
                 accessKeyId:(NSString * _Nonnull)accessKeyId
             accesskeySecret:(NSString * _Nonnull)accesskeySecret;


/**公共云DNS和融合云DNS同时配置时，设置主用DNS解析失败多少次后自动降级到备用DNS来兜底，如果只配置一种DNS,不需要设置该方法
 *
 * 设置主用DNS解析失败多少次后自动降级到备用DNS来兜底，如果只配置一种DNS,不需要设置该方法
 * @param fallbackThreshold 次数（主用公共DNS时默认 4，主用融合DNS时默认2）
 * 可设置范围[0-4]  设置0表示立即降级，最大4
 */
- (void)setFallbackThreshold:(NSInteger)fallbackThreshold;


///解析缓存过期时自动刷新, 以数组形式进行配置。
///示例代码：[[DNSResolver share] setKeepAliveDomains:@[@"www.aliyun.com", @"www.taobao.com"]];
///@param domains 域名数组，当前限制为最多 10个域名。
- (void)setKeepAliveDomains:(NSArray *)domains;

/// 预解析域名信息，可在程序启动时调用，加快后续域名解析速度
/// 自动感知网络环境（ipv4-only、ipv6-only、ipv4和ipv6双栈）解析得到适用于当前网络环境的ip
/// @param domainArray  域名数组
/// @param complete     解析完成后回调
- (void)preloadDomains:(NSArray<NSString *> *)domainArray complete:(void(^)(void))complete;

/// 获取域名解析后的ip数组，自动感知网络环境（ipv4-only、ipv6-only、ipv4和ipv6双栈）得到适用于当前网络环境的ip
/// @param domain           域名
/// @param complete       回调(所有ip地址)
- (void)getIpsDataWithDomain:(NSString *)domain complete:(void(^)(NSArray<NSString *> *dataArray))complete;

/// 自动感知网络环境（ipv4-only、ipv6-only、ipv4和ipv6双栈）直接从缓存中获取适用于当前网络环境的ip数组，无需等待.  如无缓存，或有缓存但已过期并且enable为NO，则返回 nil
/// 如果没有缓存或者缓存过期则异步解析然后刷新缓存
/// @param domain   域名
/// @param enable   是否允许返回过期ip
- (NSArray<NSString *> *)getIpsByCacheWithDomain:(NSString *)domain andExpiredIPEnabled:(BOOL)enable;

/// 获取域名解析后的ipv4信息数组
/// @param domain           域名
/// @param complete       回调(所有域名信息)
- (void)getIpv4InfoWithDomain:(NSString *)domain complete:(void(^)(NSArray<DNSDomainInfo *> *domainInfoArray))complete;

/// 获取域名解析后的ipv6信息数组
/// @param domain           域名
/// @param complete       回调(所有域名信息)
- (void)getIpv6InfoWithDomain:(NSString *)domain complete:(void(^)(NSArray<DNSDomainInfo *> *domainInfoArray))complete;

/// 获取域名解析后的ipv4信息
/// @param domain           域名
/// @param complete       回调(所有域名信息中ip测量最快的一个)
- (void)getRandomIpv4InfoWithDomain:(NSString *)domain complete:(void(^)(DNSDomainInfo *domainInfo))complete;

/// 获取域名解析后的ipv6信息
/// @param domain           域名
/// @param complete       回调(所有域名信息中ip测量最快的一个)
- (void)getRandomIpv6InfoWithDomain:(NSString *)domain complete:(void(^)(DNSDomainInfo *domainInfo))complete;

/// 获取域名解析后的ipv4地址数组
/// @param domain           域名
/// @param complete       回调(所有ip地址)
- (void)getIpv4DataWithDomain:(NSString *)domain complete:(void(^)(NSArray<NSString *> *dataArray))complete;

/// 获取域名解析后的ipv6地址数组
/// @param domain           域名
/// @param complete       回调(所有ip地址)
- (void)getIpv6DataWithDomain:(NSString *)domain complete:(void(^)(NSArray<NSString *> *dataArray))complete;

/// 获取域名解析后的ipv4地址
/// @param domain            域名
/// @param complete        回调(所有ip地址中ip测量最快的一个)
- (void)getRandomIpv4DataWithDomain:(NSString *)domain complete:(void(^)(NSString *data))complete;

/// 获取域名解析后的ipv6地址
/// @param domain            域名
/// @param complete        回调(所有ip地址中ip测量最快的一个)
- (void)getRandomIpv6DataWithDomain:(NSString *)domain complete:(void(^)(NSString *data))complete;

/// 预解析域名ipv4信息，可在程序启动时调用，加快后续域名解析速度
/// @param domainArray  域名数组
/// @param complete     解析完成后回调
- (void)preloadIpv4Domains:(NSArray<NSString *> *)domainArray complete:(void(^)(void))complete;

/// 预解析域名ipv6信息，可在程序启动时调用，加快后续域名解析速度
/// @param domainArray  域名数组
/// @param complete     解析完成后回调
- (void)preloadIpv6Domains:(NSArray<NSString *> *)domainArray complete:(void(^)(void))complete;

/// 直接从缓存中获取ipv4解析结果，无需等待.  如无缓存，或有缓存但已过期，并且enable为NO，则返回 nil
/// 如果没有缓存或者缓存过期则异步解析然后刷新缓存
/// @param domain   域名
/// @param enable   是否允许返回过期ip
- (NSArray<NSString *> *)getIpv4ByCacheWithDomain:(NSString *)domain andExpiredIPEnabled:(BOOL)enable;

/// 直接从缓存中获取ipv6解析结果，无需等待.  如无缓存，或有缓存但已过期，并且enable为NO，则返回 nil
/// 如果没有缓存或者缓存过期则异步解析然后刷新缓存
/// @param domain   域名
/// @param enable   是否允许返回过期ip
- (NSArray<NSString *> *)getIpv6ByCacheWithDomain:(NSString *_Nonnull)domain andExpiredIPEnabled:(BOOL)enable;

///hostArray为需要清除的host域名数组。如果需要清空全部数据，传nil或者空数组即可
///示例代码：[[DNSResolver share] clearHostCache:@[@"www.aliyun.com", @"www.taobao.com"]];
-(void)clearHostCache:(NSArray <NSString *>*)hostArray;

///数据收集分析
- (NSArray *)getRequestReportInfo;
@end


