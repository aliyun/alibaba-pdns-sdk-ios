//
//  DNSLog_Internal.h
//  AlicloudDNS
//
//  Created by junmo on 2018/12/19.
//  Copyright © 2018年 alibaba-inc.com. All rights reserved.
//

#import "DNSLoggerDelegate.h"
#import "DNSLog.h"

// logHandler输出日志，不受日志开关影响
#define DNSLogDebug(frmt, ...)\
if ([DNSLog validLogHandler]) {\
    NSString *logFormat = [NSString stringWithFormat:@"%s", frmt];\
    NSString *logStr = [NSString stringWithFormat:logFormat, ##__VA_ARGS__, nil];\
    [DNSLog outputToLogHandler:logStr];\
}\
if ([DNSLog isEnabled]) {\
    NSLog((@"%s [Line %d] " frmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);\
}

@interface DNSLog ()

+ (void)setLogHandler:(id<DNSLoggerProtocol>)handler;
+ (BOOL)validLogHandler;
+ (void)outputToLogHandler:(NSString *)logStr;

@end
