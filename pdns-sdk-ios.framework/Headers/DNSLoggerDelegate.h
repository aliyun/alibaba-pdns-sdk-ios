//
//  DNSLoggerProtocol.h
//  AlicloudDNS
//
//  Created by junmo on 2018/12/19.
//  Copyright © 2018年 alibaba-inc.com. All rights reserved.
//

#ifndef DNSLoggerProtocol_h
#define DNSLoggerProtocol_h

#import <Foundation/Foundation.h>

@protocol DNSLoggerProtocol <NSObject>

- (void)log:(NSString *)logStr;

@end

#endif /* DNSLoggerProtocol_h */
