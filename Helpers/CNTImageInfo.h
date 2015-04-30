//
//  CNTImageInfo.h
//  Connect SDK
//
//  Created by Jeremy White on 8/14/14.
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
 * Normalized reference object for information about an image to be sent to a device through the CNTMediaPlayer capability.
 */
@interface CNTImageInfo : NSObject

/*!
 * Enumerated value of the type of image that each CNTImageInfo instance will represent. Default is unknown.
 */
enum {
    /*! Unknown to the SDK, may not be used unless you extend Connect SDK to add additional functionality */
    CNTImageTypeUnknown,

    /*! Icon or thumbnail image; mostly used by the CNTMediaPlayer capability to provide an icon for media playback. */
    CNTImageTypeThumb,

    /*! Large-sized poster image for use by CNTMediaPlayer capability when displaying video. It is recommended that your poster image is the same size as the target video player (full HD, in most cases). */
    CNTImageTypeVideoPoster,

    /*! Album art image for use when playing audio through the CNTMediaPlayer capability. */
    CNTImageTypeAlbumArt
};
typedef NSUInteger CNTImageType;

/*! URL source of the image */
@property (nonatomic, strong) NSURL *url;

/*! Type of image (see CNTImageType enum) */
@property (nonatomic) CNTImageType type;

/*! Width of the image (optional) */
@property (nonatomic) NSInteger width;

/*! Height of the image (optional) */
@property (nonatomic) NSInteger height;

/*!
 * Creates an instance of CNTImageInfo with given property values.
 *
 * @param url URL source of the image
 * @param type Type of image (see CNTImageType enum)
 */
- (instancetype) initWithURL:(NSURL *)url type:(CNTImageType)type;

@end
