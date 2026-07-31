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

#import <Foundation/Foundation.h>

@interface DNSDomainInfo : NSObject

///所要解析的domain name
@property (nonatomic, copy) NSString *domain;
///domain name被解析后的对应的ip地址
@property (nonatomic, copy) NSString *data;
///解析器类型：PublicDNS / FusionDNS / LocalDNS（取值参见 DNSConst.h 中 RESOLVER_* 常量）
@property (nonatomic, copy) NSString *resolverType;
///缓存写入场景：@"0" 同步解析 / @"1" preload预解析 / @"2" 取缓存的异步刷新 / @"3" 定时刷新（取值参见 SCENE_* 常量）
@property (nonatomic, copy) NSString *scene;

///是否已有真实测速结果（delayTimes 是否非空）。用于区分"未测速"与"已测速"，不能用 speedTestTime==5000 判断
- (BOOL)hasSpeedResult;

@end
