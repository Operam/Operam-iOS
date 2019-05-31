//
//  Operam_Constants.h
//  Framework
//
//  Created by Joao Prado Maia on 4/17/19.
//  Copyright © 2019 Ipanema Labs LLC. All rights reserved.
//

#ifndef Operam_Constants_h
#define Operam_Constants_h

typedef NS_ENUM(NSInteger, OperamLogLevel) {
    OperamLogLevelInfo,
    OperamLogLevelError,
    OperamLogLevelDebug
};

typedef NS_ENUM(NSInteger, OperamProcessType) {
    OperamProcessTypeShakeGesture,
    OperamProcessTypeManual,
    OperamProcessTypeScreenshot
};

#define Operam_Log(logLevel, functionName, frmt, ...)    \
    do {                                                 \
        [[Operam sharedInstance]                         \
                logWithLevel:logLevel                    \
                file:__FILE__                            \
                function:functionName                    \
                line:__LINE__                            \
                format:(frmt), ## __VA_ARGS__];          \
    } while (0)

#define OperamLogError(frmt, ...) \
    Operam_Log(OperamLogLevelError, __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)

#define OperamLogInfo(frmt, ...)  \
    Operam_Log(OperamLogLevelInfo, __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)

#define OperamLogDebug(frmt, ...) \
    Operam_Log(OperamLogLevelDebug, __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)

#define Operam_Event(functionName, title, attachmentsEnabled)   \
    do {                                                        \
        [[Operam sharedInstance]                                \
                recordEvent:title                               \
                file:__FILE__                                   \
                function:functionName                           \
                line:__LINE__                                   \
                includeAttachments:attachmentsEnabled];         \
    } while (0)

#define OperamCreateEventWithAttachments(title) \
    Operam_Event(__PRETTY_FUNCTION__, title, YES)

#define OperamCreateEvent(title) \
    Operam_Event(__PRETTY_FUNCTION__, title, NO)


#endif /* Operam_Constants_h */
