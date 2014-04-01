//
//  SmartScanner.h
//  SmartScanner
//
//  Copyright (c) 2014 Icare Research Institute. All rights reserved
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
//  FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
//  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
//  IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
//  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//



/** This protocol must be implemented to receive smartscan messages.

The default message is when a code is returned.

*/



#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>


#import "SmartIDScanTypes.h"

@class SmartScanner;

/** This protocol allows to get messages from SmartScanner. These messages can be the content of a code or an error with your current use of the library.

 */
@protocol SmartScannerDelegate <NSObject>

/**---------------------------------------------------------------------------------------
* @name SmartScanner events
*  ---------------------------------------------------------------------------------------
*/

/** This is the protocol used to inform when a code is found.
 


@param smartScan smartScanner object
@param aCode the code found
@param aType the type of code found (refering to the enum in CodeTypes.h)

*/

-(void)SmartScannerFoundCode:(SmartScanner*)smartScan code:(NSString*) aCode ofType:(int)aType;
    
/**---------------------------------------------------------------------------------------
 * @name SmartScanner events
 *  ---------------------------------------------------------------------------------------
 */

/** This is the protocol used to inform when an error occured

 Errors can happen if you try to set a zone of interest bigger than the stream isself, or try to decode a type that is not activated in the current build.

 @param SmartScanner smartScanner object
 @param aError String description of the error
 
*/
    
-(void)SmartScanner:(SmartScanner*)smartScan errorOccured:(NSString*)aError;

@end



/** This class contains the main access to the smartscanner library.

Provides all the functions needed to manipulate the camera stream, and the decoding functions/options

*/

@interface SmartScanner : NSObject

@property(assign, nonatomic)id<SmartScannerDelegate> scDelegate;

//base

/**---------------------------------------------------------------------------------------
* @name Initialization
*  ---------------------------------------------------------------------------------------
*/

/** Basic constructor

allows to init the SmartScanner. When the scanner is initialized with this function you'll need to use the setDecodingType: function.
 
  @return SmartScanner instance
*/

-(id) init;

/**---------------------------------------------------------------------------------------
 * @name Initialization
 *  ---------------------------------------------------------------------------------------
 */

/** Init the smartscanner and set the decoding type you want in one line.
 
 allows to init the SmartScanner.
 
 @param aDecodeType SmartDecodingTypes you want to be decoded
 @return SmartScanner instance
 */


-(id)initWithDecodingType:(SmartDecodingTypes)aDecodeType;


/**---------------------------------------------------------------------------------------
* @name Create the video stream view
*  ---------------------------------------------------------------------------------------
*/

/** Retrieve a view containing the camera stream of the given size
 
 Allows to retrieve an UIView containing the camera stream, and starts the decoding.
 
 @return UIView that can be manipulated and added to any other view
 
 @param aRect Desirated size for the camera view.


*/
-(UIView*)previewViewWithViewSize:(CGRect) aRect;
/**---------------------------------------------------------------------------------------
* @name Destruction
*  ---------------------------------------------------------------------------------------
*/

/** Close the smartscanner object and video stream relative objects
 
 Should be used when you don't need to use the smartscanner anymore


*/
-(void)closeCameraStream;
/**---------------------------------------------------------------------------------------
* @name Tool
*  ---------------------------------------------------------------------------------------
*/

/** Use the flash light as a torche
 
 Allows to turn ON/OFF the flash light to help decoding in case of bad lighting

@param aValue the dedirated state of the light
 
*/
-(void)setFlashEnabled:(bool)aValue;

/**---------------------------------------------------------------------------------------
 * @name Tool
 *  ---------------------------------------------------------------------------------------
 */

/** Retrieve a string corresponding to the code type
 
 Retrieve a string description of a SmartDecodingType. It can be usefull in the case where you are decoding multiple types and want more details about the which type has actually been decoded.
 
 @param aCodeType type of code
 @return NSString
 
 */
-(NSString*)getCodeTypeString:(SmartDecodingTypes)aCodeType;

/**---------------------------------------------------------------------------------------
 * @name Decoder configuration
 *  ---------------------------------------------------------------------------------------
 */

/** Set the zone of interest to scan
 
 Allows to set which zone in the video stream (640 X 480) will be scanned.
 
 @param aTargetRect A rectangle that must be within the video stream
 
 @return the zone of interest relative to the previewView
 
 
 */
-(CGRect)setRegionOfInterest:(CGRect)aTargetRec;

    
/**---------------------------------------------------------------------------------------
 * @name Decoder configuration
 *  ---------------------------------------------------------------------------------------
 */

/** Set the decoding orientation
 
 When using any type of OCR decoding, the default orientation will be landscape right (with home button on the right) If you want to use any other orientation while decoding, you should specify the orientation you want with this function
 
 @param aOrientation UIDeviceOrientation you want to use for ocr decoding
 

 
 
 */
-(void)setDecodingOrientation:(UIDeviceOrientation)aOrientation;
    


//Decoding config
/**---------------------------------------------------------------------------------------
* @name Decoder configuration
*  ---------------------------------------------------------------------------------------
*/

/** Enable decoding
 
 allows to enable/disable the decoding without closing the video stream
 
 @param aEnable bool representing the desirated decoding state


*/
-(void)enableDecoding:(bool)aEnable;



/**---------------------------------------------------------------------------------------
* @name Decoder configuration
*  ---------------------------------------------------------------------------------------
*/

/** Allows to select the type of code you want to scan

Refers to SmartIDScanTypes.h
 
multiple codes can be activated at the same time using '|' like
 
    [mySmartScanner setDecodingType: CODE_PLATES | CODE_1D2D_ALL]
 
 But any type you will add that you don't need will add an additional computation time in the decoding procedure
 
 @param aDecodeType Type of code

*/
-(CGRect)setDecodingType:(SmartDecodingTypes)aDecodeType;
    
//adusting camera
/**---------------------------------------------------------------------------------------
 * @name Decoder configuration
 *  ---------------------------------------------------------------------------------------
 */

/** Set the focus point of the camera
 
 Allows to manually set the focus zone of the camera
 
 @param aPoint CGpoint (values between 0.0 and 1.0) representing where in the stream the camera should do the autofocus
 
 */
    
-(void)continuousFocusAtPoint:(CGPoint)aPoint;





//info
/**---------------------------------------------------------------------------------------
* @name Properties
*  ---------------------------------------------------------------------------------------
*/

/** Retrieve the smartscanner and decoding type versions


 */
-(NSString*)version;

/**
 Zone of interest (zone where the smartscanner will try to find a code) relative to the previewView
 */


-(CGRect)regionOfInterest;

@end


