//
//  CNTCapability.h
//  Connect SDK
//
//  Created by Jeremy White on 12/26/13.
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

/*!
 * CNTCapabilityPriorityLevel values are used by CNTConnectableDevice to find the most suitable CNTDeviceService capability to be presented to the user. Values of VeryLow and VeryHigh are not in use internally the SDK. Connect SDK uses Low, Normal, and High internally.
 *
 * Default behavior:
 * If you are unsatisfied with the default priority levels & behavior of Connect SDK, it is possible to subclass a particular CNTDeviceService and provide your own value for each capability. That CNTDeviceService subclass would need to be registered with CNTDiscoveryManager.
 */
typedef enum {
    CNTCapabilityPriorityLevelVeryLow = 1,
    CNTCapabilityPriorityLevelLow = 25,
    CNTCapabilityPriorityLevelNormal = 50,
    CNTCapabilityPriorityLevelHigh = 75,
    CNTCapabilityPriorityLevelVeryHigh = 100
} CNTCapabilityPriorityLevel;

/*!
 * Generic asynchronous operation response success handler block. If there is any response data to be processed, it will be provided via the responseObject parameter.
 *
 * @param responseObject Contains the output data as a generic object reference. This value may be any of a number of types (NSString, NSDictionary, NSArray, etc). It is also possible that responseObject will be nil for operations that don't require data to be returned (move mouse, send key code, etc).
 */
typedef void (^CNTSuccessBlock)(id responseObject);

/*!
 * Generic asynchronous operation response error handler block. In all cases, you will get a valid NSError object. Connect SDK will make all attempts to give you the lowest-level error possible. In cases where an error is generated by Connect SDK, an enumerated error code (CNTConnectStatusCode) will be present on the NSError object.
 *
 * ###Low-level error example
 * ####Situation
 * Connect SDK receives invalid XML from a device, generating a parsing error
 *
 * ####Result
 * Connect SDK will call the CNTFailureBlock and pass off the NSError generated during parsing of the XML.
 *
 * ###High-level error example
 * ####Situation
 * An invalid value is passed to a device capability method
 *
 * ####Result
 * The capability method will immediately invoke the CNTFailureBlock and pass off an NSError object with a status code of CNTConnectStatusCodeArgumentError.
 *
 * @param error NSError object describing the nature of the problem. Error descriptions are not localized and mostly intended for developer use. It is not recommended to display most error descriptions in UI elements.
 */
typedef void (^CNTFailureBlock)(NSError *error);
