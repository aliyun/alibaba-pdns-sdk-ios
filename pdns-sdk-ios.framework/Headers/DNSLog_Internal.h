//
// DNSLog_Internal.h
// 健康检查器：用于探测熔断后的 DNS 服务器是否恢复
//
// Created by issuser on 2025/9/18.
// Copyright © 2025 alidns. All rights reserved.
//

#import "DNSLoggerDelegate.h"
#import "DNSLog.h"

// logHandler输出日志，不受日志开关影响

#define DNSLogDebug(frmt, ...) \
    do { \
        if ([DNSLog validLogHandler]) { \
            /* 修复：直接用 %@ 而不是先转成C字符串再格式化 */ \
            NSString *logStr = [NSString stringWithFormat:@"pdns: " frmt, ##__VA_ARGS__]; \
            [DNSLog outputToLogHandler:logStr]; \
        } \
        if ([DNSLog isEnabled]) { \
            static NSDateFormatter *formatter; \
            static dispatch_once_t onceToken; \
            dispatch_once(&onceToken, ^{ \
                formatter = [[NSDateFormatter alloc] init]; \
                [formatter setDateFormat:@"yyyy-MM-dd HH:mm:ss.SSS"]; \
            }); \
            NSString *timestamp = [formatter stringFromDate:[NSDate date]]; \
            NSLog(@"%@ %s [Line %d] pdns: " frmt, \
                  timestamp, \
                  __PRETTY_FUNCTION__, \
                  __LINE__, \
                  ##__VA_ARGS__); \
        } \
    } while(0)



@interface DNSLog ()

+ (void)setLogHandler:(id<DNSLoggerProtocol>)handler;
+ (BOOL)validLogHandler;
+ (void)outputToLogHandler:(NSString *)logStr;

@end
