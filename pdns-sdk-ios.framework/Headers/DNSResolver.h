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
//  当前版本：2.2.1

#import <Foundation/Foundation.h>
#import "DNSDomainInfo.h"

typedef NS_OPTIONS(NSUInteger, DNSResolverScheme) {
    DNSResolverSchemeHttp     = 0,
    DNSResolverSchemeHttps    = 1 << 0
};

@interface DNSResolver : NSObject

/// 唯一初始化方法
+ (instancetype)share;

//控制台注册生成，必传参数，该参数设置未来会被弃用，替换为- (void)setAccountId:(NSString *)accountId andAccessKeyId:(NSString *)accessKeyId andAccesskeySecret:(NSString *)accesskeySecret;方法设置
@property (nonatomic, strong) NSString *accountId;

//控制台生成鉴权参数，必传参数，该参数设置未来会被弃用，替换为- (void)setAccountId:(NSString *)accountId andAccessKeyId:(NSString *)accessKeyId andAccesskeySecret:(NSString *)accesskeySecret;方法设置
@property (nonatomic, strong) NSString *accessKeyId;

//控制台生成鉴权参数，必传参数，该参数设置未来会被弃用，替换为- (void)setAccountId:(NSString *)accountId andAccessKeyId:(NSString *)accessKeyId andAccesskeySecret:(NSString *)accesskeySecret;方法设置
@property (nonatomic, strong) NSString *accesskeySecret;

///是否开启缓存， 默认为YES
@property (nonatomic, assign) BOOL cacheEnable;

//是否区分不同网络下的缓存数据， 默认为YES
@property (nonatomic, assign) BOOL ispEnable;

//是否开启IP测速， 默认为NO
@property (nonatomic, assign) BOOL speedTestEnable;

///设置测速方式,默认为0（icmp探测），不为0（socket端口建连探测）例如：80/443
@property (nonatomic, assign) int speedPort;

///是否只获取域名对应的ip， 默认为NO
@property (nonatomic, assign) BOOL shortEnable;

///是否使用ipv6网络解析域名，默认为NO
@property (nonatomic, assign) BOOL ipv6Enable;

///最大的否定缓存ttl配置，默认30s
@property (nonatomic, assign) double maxNegativeCache;

///最大的缓存ttl配置，默认3600s
@property (nonatomic, assign) double maxCacheTTL;

///DNS scheme 类型， 默认为：DNSResolverSchemeHttps
@property (nonatomic, assign) DNSResolverScheme scheme;

///域名解析缓存最大数量，默认为100个域名
@property (nonatomic, assign) NSInteger cacheCountLimit;

///解析超时时间，建议2~5s，默认3s
@property (nonatomic, assign) NSTimeInterval timeout;

///缓存永久有效
@property (nonatomic, assign) BOOL immutableCacheEnable;

///是否开启localdns兜底
@property (nonatomic, assign) BOOL localdnsEnable;

///设置ecs地址
@property (nonatomic, copy) NSString *ednsSubnet;

+ (void)enableLog;

+ (void)disableLog;
//获取SessionId
- (NSString *)getSessionId;

//控制台注册生成
- (void)setAccountId:(NSString *)accountId andAccessKeyId:(NSString *)accessKeyId andAccesskeySecret:(NSString *)accesskeySecret;

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
/// @param domain   域名
/// @param enable   是否允许返回过期ip
- (NSArray<NSString *> *)getIpv4ByCacheWithDomain:(NSString *)domain andExpiredIPEnabled:(BOOL)enable;

/// 直接从缓存中获取ipv6解析结果，无需等待.  如无缓存，或有缓存但已过期，并且enable为NO，则返回 nil
/// @param domain   域名
/// @param enable   是否允许返回过期ip
- (NSArray<NSString *> *)getIpv6ByCacheWithDomain:(NSString *)domain andExpiredIPEnabled:(BOOL)enable;

///hostArray为需要清除的host域名数组。如果需要清空全部数据，传nil或者空数组即可
///示例代码：[[DNSResolver share] clearHostCache:@[@"www.aliyun.com", @"www.taobao.com"]];
-(void)clearHostCache:(NSArray <NSString *>*)hostArray;

///数据收集分析
- (NSArray *)getRequestReportInfo;
@end


