//
//  Operam.h
//  Operam
//
//  Created by Joao Prado Maia on 6/16/16.
//  Copyright © 2016 Ipanema Labs LLC. All rights reserved.
//

#import <Foundation/Foundation.h>

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


NS_ASSUME_NONNULL_BEGIN

@class Operam;


@protocol OperamDelegate <NSObject>

- (void)operamDidGenerateUserIssueSubmission:(Operam *)operam;

@optional
- (BOOL)operamShouldDisplayConfirmationMessage:(Operam *)operam;
- (BOOL)operamShouldDisplayInstructionView:(Operam *)operam;

@end


@interface Operam : NSObject

/**
 *  API key associated with this Operam account.
 */
@property (nonatomic, copy, readonly) NSString *apiKey;

/**
 *  Version number of the Operam framework.
 */
@property (nonatomic, copy, readonly) NSString *version;

/**
 *  Whether to log debug information within the Operam framework itself. 
 *  Probably best not to enable this feature on production builds.
 */
@property (nonatomic, assign) BOOL debug;

/**
 *  Whether to optimize the final size of the screenshot to use less bandwidth.
 *  Defaults to YES.
 */
@property (nonatomic, assign) BOOL optimizeScreenshot;

/**
 *  Whether to collect the contents of NSUserDefaults for every issue/event.
 *  Defaults to YES.
 */
@property (nonatomic, assign) BOOL collectUserDefaults;

/**
 *  The OperamProcessType that decides how an issue submission is launched.
 *  - OperamProcessTypeShakeGesture - shake device
 *  - OperamProcessTypeManual - call the `presentReportIssueController` method
 *  - OperamProcessTypeScreenshot - press the home and power buttons at the same time
 */
@property (nonatomic, assign, readonly) OperamProcessType processType;

/**
 *  The Operam delegate to customize some of the available functionality.
 */
@property (nonatomic, weak) id<OperamDelegate> delegate;

/**
 *  Access the singleton Operam instance.
 *
 *  @return The Operam instance
 */
+ (instancetype)sharedInstance NS_SWIFT_NAME(shared());

/**
 *  Takes a screenshot of what is being displayed to the user, and presents 
 *  the issue reporting interface.
 */
- (void)presentReportIssueController;

/**
 *  Starts up the Operam infrastructure for your application, identified by the
 *  given API key. It will use the default OperamProcessTypeShakeGesture.
 *
 *  @param apiKey The Operam API key for this application
 *
 *  @return The Operam instance
 */
+ (instancetype)startWithAPIKey:(NSString *)apiKey;

/**
 *  Starts up the Operam infrastructure for your application, identified by the
 *  given API key. It will use the default OperamProcessTypeShakeGesture.
 *
 *  @param apiKey The Operam API key for this application
 *  @param processType The process to trigger the reporting interface
 *
 *  @return The Operam instance
 */
+ (instancetype)startWithAPIKey:(NSString *)apiKey processType:(OperamProcessType)processType;

/**
 *  Alternate factory method which allows the debug mode to be enabled from
 *  the beginning.
 *
 *  @param apiKey The Operam API key for this application
 *  @param processType The process to trigger the reporting interface
 *  @param debug Whether to process things in debug mode
 *
 *  @return The Operam instance
 */
+ (instancetype)startWithAPIKey:(NSString *)apiKey processType:(OperamProcessType)processType debug:(BOOL)debug;

/**
 *  Sets the user identifier for the current user session.
 *
 *  @param identifier The user's identifier
 */
- (void)setUserIdentifier:(nullable NSString *)identifier;

/**
 *  Sets the username for the current user session.
 *
 *  @param username The user's username
 */
- (void)setUsername:(nullable NSString *)username;

/**
 *  Sets the full name for the current user session.
 *
 *  @param fullName The user's full name
 */
- (void)setUserFullName:(nullable NSString *)fullName;

/**
 *  Sets the email address for the current user session.
 *
 *  @param email The user's email address
 */
- (void)setUserEmail:(nullable NSString *)email;

/**
 *  Stores a dictionary (as a JSON encoded string) for a given key.
 *
 *  @param dict The dictionary to store
 *  @param key The key to use
 */
- (void)setDictionary:(nullable NSDictionary *)dict forKey:(NSString *)key;

/**
 *  Stores a string for a given key.
 *
 *  @param value The string to store
 *  @param key The key to use
 */
- (void)setString:(nullable NSString *)value forKey:(NSString *)key;

/**
 *  Stores an integer value for a given key.
 *
 *  @param value The integer value to store
 *  @param key The key to use
 */
- (void)setIntValue:(NSInteger)value forKey:(NSString *)key;

/**
 *  Stores a boolean for a given key.
 *
 *  @param value The boolean to store
 *  @param key The key to use
 */
- (void)setBoolValue:(BOOL)value forKey:(NSString *)key;

/**
 *  Stores a float for a given key.
 *
 *  @param value The float to store
 *  @param key The key to use
 */
- (void)setFloatValue:(float)value forKey:(NSString *)key;

/**
 *  Records an event with the given message. This is used by the macro, should not be called itself explicitly.
 *
 *  Call OperamCreateEvent(NSString *message) to create an event submission with a message, without files attached.
 *  Call OperamCreateEventWithAttachments(NSString *message) to create an event submission with a message, With files attached.
 *
 *  @param title    The message to be included with this submission.
 *  @param file     The file that this function is being called from.
 *  @param function The name of the function calling this function.
 *  @param line     The line number of the call to this function.
 *  @param includeAttachments   Whether or not files attached to Operam will be included with this event submission.
 */
- (void)recordEvent:(NSString *)title file:(const char *)file function:(const char *)function line:(int)line includeAttachments:(BOOL)includeAttachments;

/**
 *  Takes in a message and logs it as a debugging message.
 *  This is used by the macro, should not be called itself explicitly.
 *
 *  Call OperamLogError(NSString *message) to log a message to the debug_logs file, marked as an error message.
 *  Call OperamLogInfo(NSString *message) to log a message to the debug_logs file, marked as an info message.
 *  Call OperamLogDebug(NSString *message) to log a message to the debug_logs file, marked as an debug message.
 *
 *  Includes the filename, method name, and line number of its call.
 *
 *  @param logLevel The type of log message associated with this log call.
 *  @param file     The file that this function is being called from.
 *  @param function The function that contains the call to this function.
 *  @param line     The line number the call to this function is on.
 *  @param format   The message to be associated with the call to this function.
 */
- (void)logWithLevel:(OperamLogLevel)logLevel file:(const char *)file function:(const char *)function line:(int)line format:(NSString *)format, ... NS_FORMAT_FUNCTION(5,6);

/**
 *  Takes in a message and logs it as a debugging message.
 *
 *  Includes the filename, method name, and line number of its call.
 *
 *  @param msg      The message that should be logged.
 *  @param logLevel The type of log message associated with this log call.
 *  @param file     The file that this function is being called from.
 *  @param function The function that contains the call to this function.
 *  @param line     The line number the call to this function is on.
 */
- (void)logMessage:(NSString *)msg level:(OperamLogLevel)logLevel file:(const char *)file function:(const char *)function line:(int)line;

/**
 *  Takes in the url of a file and adds it to the list of attachments to be included with all submissions.
 *
 *  @param fileUrl The url of a file to be included with all submissions.
 *
 *  @return YES if the file passes the filesize limit (100kb) and is successfully added, NO otherwise.
 */
- (BOOL)addAttachmentWithFileUrl:(NSURL *)fileUrl;

/**
 *  Takes in the url of a file and removes it from the list of attachments to be included with all submissions.
 *
 *  @param fileUrl The url of a file to no longer be included with all submissions.
 */
- (void)removeAttachmentWithFileUrl:(NSURL *)fileUrl;

/**
 *  Clears the list of attachments to be included with all submissions.
 */
- (void)clearAttachments;

/**
 *  Begins timing for the following key.
 *
 *  @param key The key associated with the elapsed time measurement.
 */
- (void)startTrackingTimeForKey:(NSString *)key;

/**
 *  Ends timing for the following key. Elapsed time is reported in an Issue Submission.
 *
 *  @param key The key associated with the elapsed time measurement.
 */
- (void)stopTrackingTimeForKey:(NSString *)key;

/**
 * Operam should not be initialized directly -- call +[Operam sharedInstance] to
 * properly configure the Operam singleton.
 */
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
