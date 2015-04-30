//
//  CNTWebAppSession.h
//  Connect SDK
//
//  Created by Jeremy White on 2/21/14.
//  Copyright (c) 2014 LG Electronics.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#import <Foundation/Foundation.h>
#import "CNTCapability.h"
#import "CNTDeviceService.h"
#import "CNTMediaPlayer.h"
#import "CNTMediaControl.h"
#import "CNTServiceCommandDelegate.h"
#import "CNTLaunchSession.h"
#import "CNTWebAppSessionDelegate.h"

/*! Status of the web app */
typedef enum {
    /*! Web app status is unknown */
    CNTWebAppStatusUnknown,

    /*! Web app is running and in the foreground */
    CNTWebAppStatusOpen,

    /*! Web app is running and in the background */
    CNTWebAppStatusBackground,

    /*! Web app is in the foreground but has not started running yet */
    CNTWebAppStatusForeground,

    /*! Web app is not running and is not in the foreground or background */
    CNTWebAppStatusClosed
} CNTWebAppStatus;


/*!
 * ###Overview
 * When a web app is launched on a first screen device, there are certain tasks that can be performed with that web app. CNTWebAppSession serves as a second screen reference of the web app that was launched. It behaves similarly to CNTLaunchSession, but is not nearly as static.
 *
 * ###In Depth
 * On top of maintaining session information (contained in the launchSession property), CNTWebAppSession provides access to a number of capabilities.
 * - CNTMediaPlayer
 * - CNTMediaControl
 * - Bi-directional communication with web app
 *
 * CNTMediaPlayer and CNTMediaControl are provided to allow for the most common first screen use cases -- a media player (audio, video, & images).
 *
 * The Connect SDK JavaScript Bridge has been produced to provide normalized support for these capabilities across protocols (Chromecast, webOS, etc).
 */
@interface CNTWebAppSession : NSObject <CNTServiceCommandDelegate, CNTMediaPlayer, CNTMediaControl, CNTJSONObjectCoding>

// @cond INTERNAL
// This is only being used in CNTWebOSWebAppSession, but could be useful in other places in the future
typedef void (^CNTWebAppMessageBlock)(id message);
// @endcond

/*!
 * Success block that is called upon successfully getting a web app's status.
 *
 * @param status The current running & foreground status of the web app
 */
typedef void (^CNTWebAppStatusBlock)(CNTWebAppStatus status);

/*!
 * Success block that is called upon successfully getting a web app's status.
 *
 * @param status The current running & foreground status of the web app
 */
typedef void (^CNTWebAppPinStatusBlock)(BOOL status);

/*!
 * CNTLaunchSession object containing key session information. Much of this information is required for web app messaging & closing the web app.
 */
@property (nonatomic, strong) CNTLaunchSession *launchSession;

/*!
 * CNTDeviceService that was responsible for launching this web app.
 */
@property (nonatomic, weak, readonly) CNTDeviceService *service;

/*!
 * Instantiates a CNTWebAppSession object with all the information necessary to interact with a web app.
 *
 * @param launchSession CNTLaunchSession containing info about the web app session
 * @param service CNTDeviceService that was responsible for launching this web app
 */
- (instancetype) initWithLaunchSession:(CNTLaunchSession *)launchSession service:(CNTDeviceService *)service;

/*!
 * Subscribes to changes in the web app's status.
 *
 * @param success (optional) CNTWebAppStatusBlock to be called on app status change
 * @param failure (optional) CNTFailureBlock to be called on failure
 */
- (CNTServiceSubscription *) subscribeWebAppStatus:(CNTWebAppStatusBlock)success failure:(CNTFailureBlock)failure;

/*!
 * Join an active web app without launching/relaunching. If the app is not running/joinable, the failure block will be called immediately.
 *
 * @param success (optional) CNTSuccessBlock to be called on join success
 * @param failure (optional) CNTFailureBlock to be called on failure
 */
- (void) joinWithSuccess:(CNTSuccessBlock)success failure:(CNTFailureBlock)failure;

/*!
 * Closes the web app on the first screen device.
 *
 * @param success (optional) CNTSuccessBlock to be called on success
 * @param failure (optional) CNTFailureBlock to be called on failure
 */
- (void) closeWithSuccess:(CNTSuccessBlock)success failure:(CNTFailureBlock)failure;

#pragma mark - Connection handling

/*!
 * Establishes a communication channel with the web app.
 *
 * @param success (optional) CNTSuccessBlock to be called on success
 * @param failure (optional) CNTFailureBlock to be called on failure
 */
- (void) connectWithSuccess:(CNTSuccessBlock)success failure:(CNTFailureBlock)failure;

/*!
 * Closes any open communication channel with the web app.
 */
- (void) disconnectFromWebApp;

/*!
 * Pin the web app on the launcher.
 *
 * @param webAppId NSString webAppId to be pinned.
 */
- (void)pinWebApp:(NSString *)webAppId success:(CNTSuccessBlock)success failure:(CNTFailureBlock)failure;

/*!
 * UnPin the web app on the launcher.
 *
 * @param webAppId NSString webAppId to be unpinned.
 */
- (void)unPinWebApp:(NSString *)webAppId success:(CNTSuccessBlock)success failure:(CNTFailureBlock)failure;

/*!
 * To check if the web app is pinned or not
 */
- (void)isWebAppPinned:(NSString *)webAppId success:(CNTWebAppPinStatusBlock)success failure:(CNTFailureBlock)failure;

#pragma mark - Communication

/*!
 * When messages are received from a web app, they are parsed into the appropriate object type (string vs JSON/NSDictionary) and routed to the CNTWebAppSessionDelegate.
 */
@property (nonatomic, strong) id<CNTWebAppSessionDelegate> delegate;

/*!
 * Sends a simple string to the web app. The Connect SDK JavaScript Bridge will receive this message and hand it off as a string object.
 *
 * @param success (optional) CNTSuccessBlock to be called on success
 * @param failure (optional) CNTFailureBlock to be called on failure
 */
- (void) sendText:(NSString *)message success:(CNTSuccessBlock)success failure:(CNTFailureBlock)failure;

/*!
 * Sends a JSON object to the web app. The Connect SDK JavaScript Bridge will receive this message and hand it off as a JavaScript object.
 *
 * @param success (optional) CNTSuccessBlock to be called on success
 * @param failure (optional) CNTFailureBlock to be called on failure
 */
- (void) sendJSON:(NSDictionary *)message success:(CNTSuccessBlock)success failure:(CNTFailureBlock)failure;

@end
