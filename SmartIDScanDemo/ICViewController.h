//
//  ICViewController.h
//  SmartScanDemo
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

#import <UIKit/UIKit.h>
#import "SmartScanner.h"


@interface ICViewController : UIViewController <SmartScannerDelegate, UIAlertViewDelegate>


@property (atomic)CGRect targetRect;

-(IBAction)torchClicked:(id)sender;
-(IBAction)streamClicked:(id)sender;

-(void)SmartScannerFoundCode:(SmartScanner*)smartScan code:(NSString*) aCode ofType:(int)aType;

-(void)SmartScanner:(SmartScanner *)smartScan errorOccured:(NSString *)aError;

@end
