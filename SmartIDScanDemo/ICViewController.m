//
//  ICViewController.m
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

#import "ICViewController.h"




//Note : You will need to uncomment the line depending on which SDK you want to test. (inpayment slips / 1D2D / swiss plates / swiss papers / insurance cards)


//1D-2D group (It is advised to avoid using every decoder at the same time to enhance the performences)

//#define TYPE_TO_DECODE CODE_QR_CODES | CODE_1D2D_BARCODES_ALL | CODE_1D2D_DATA_MATRICES
#define TYPE_TO_DECODE CODE_AZTEC_CODES
//#define TYPE_TO_DECODE CODE_1D2D_DATABARS

//Insurance Cards
//#define TYPE_TO_DECODE CODE_INSURANCE_CARDS

//Swiss Papers MRZ
//#define TYPE_TO_DECODE CODE_OCR_B_SWISS_IDS | CODE_OCR_B_SWISS_PASSPORTS | CODE_OCR_B_DRV_LICENSES

//Swiss plates
//#define TYPE_TO_DECODE CODE_PLATES

//Inpayment slips
//#define TYPE_TO_DECODE CODE_OCR_B_BVR


#ifndef TYPE_TO_DECODE
#error You must select which kind of type you want to decode by uncommenting one of the previous defines
#endif


@interface ICViewController ()
{
    
    SmartScanner* sc;
    bool videoRunning;
    UIView* _aimView;
    
    
}
@end



@implementation ICViewController

@synthesize targetRect;

- (void)viewDidLoad
{
    videoRunning = false;
    [self addObserver:self forKeyPath:@"targetRect" options:0 context:nil];
    [super viewDidLoad];
    
}



-(void)addSmartScan
{
    if(sc == nil)
        sc =  [[SmartScanner alloc] initWithDecodingType:TYPE_TO_DECODE];
    sc.scDelegate = self;
    UIView* preview = [sc previewViewWithViewSize:self.view.bounds];
    [self.view insertSubview:preview atIndex:0];
    [self setTargetRect:[sc regionOfInterest]];
    videoRunning = true;
    
    NSLog(@"SmartScanner Info : \n%@", [sc version]);
    
    
    //Note : When adding the camera, in some case you'll perhaps want your application to be in portrait only, and only the camera view displayed in landscape orientation. You can use a simple trick to rotate the camera view only
    /*
     
     CGAffineTransform transform = CGAffineTransformMakeTranslation(0,30);
     transform = CGAffineTransformRotate(transform, -M_PI_2);
     preview.center = CGPointMake(currentHeight/2,currentWight/2 );
     preview.transform = transform;
     [self.view addSubview:cameraDisplayView];
     
     */
    
    //Note : if you want to decode any OCR type, and you're not using the standard (landscape with home button on the right) orientation, you'll need to specify it to the smartscanner.
    
    [sc setDecodingOrientation: [[UIDevice currentDevice] orientation]];
    
}


-(void)viewDidAppear:(BOOL)animated
{
    
    [self addSmartScan];
    
}

-(void)removeSmartScan
{
    
    [sc closeCameraStream];
    videoRunning = false;
    sc = nil;
    
}


- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


#pragma mark - handling events

-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    
    [touches enumerateObjectsUsingBlock:^(id obj, BOOL *stop) {
        UITouch *touch = obj;
        CGPoint touchPoint = [touch locationInView:touch.view];
        [sc continuousFocusAtPoint:touchPoint];
        
    }];
}

-(IBAction)torchClicked:(id)sender
{
    static bool flashIsEnabled = false;
    
    flashIsEnabled = !flashIsEnabled;
    [sc setFlashEnabled:flashIsEnabled];
}

-(IBAction)streamClicked:(id)sender
{
    if(videoRunning)
    {
        [self removeSmartScan];
    }
    else
    {
        [self addSmartScan];
    }
}


#pragma mark - handling rotation

- (void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration
{
    [self removeSmartScan];
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation
{
    
    [self addSmartScan];
}


#pragma mark -  observed value changed

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context
{
    //Observing the advised region of interest and change the target view accordingly.
    if(_aimView == nil)
    {
        _aimView = [[UIView alloc] initWithFrame:CGRectNull];
        [[_aimView layer] setBorderWidth:3];
        [[_aimView layer] setBorderColor:[UIColor redColor].CGColor];
        [_aimView setAlpha:0.5];
        [self.view addSubview:_aimView];
        [_aimView setUserInteractionEnabled:NO];
        
    }
    
    if (object == self && [keyPath isEqualToString:@"targetRect"])
    {
        
        [_aimView setFrame: self.targetRect];
        
    }
}



-(void)displayMessageToUser:(NSString*)message
{
    
    UIAlertView* al = [[UIAlertView alloc] initWithTitle:@"Information"
                                                 message:message
                                                delegate:self
                                       cancelButtonTitle:@"Cancel"
                                       otherButtonTitles:nil];
    
    [al show];
    
}

#pragma mark -  smartscan delegate
-(void)SmartScannerFoundCode:(SmartScanner*)smartScan code:(NSString*) aCode ofType:(int)aType
{
    

    [sc enableDecoding:NO];
    NSString* message = [NSString stringWithFormat:@"SmartIDScan result : %@  with type : %@", aCode, [sc getCodeTypeString:(SmartDecodingTypes)aType]];
    NSLog(@"%@", message);
    [self displayMessageToUser:message];
    
}

-(void)SmartScanner:(SmartScanner *)smartScan errorOccured:(NSString *)aError
{
    
    NSString* message = [NSString stringWithFormat:@"SmartIDScan error : %@", aError];
    NSLog(@"%@", message);
}


#pragma mark - alertview delegate

- (void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex
{
    [sc enableDecoding:YES];
}


@end
