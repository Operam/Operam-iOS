![Operam](https://operamhq.com/images/operam_logo_blue.png)

[![CocoaPods Compatible](https://img.shields.io/cocoapods/v/Operam.svg)](https://cocoapods.org/pods/Operam)
[![Twitter](https://img.shields.io/badge/twitter-@OperamHQ-blue.svg)](https://twitter.com/OperamHQ)

Operam is a feedback / bug reporting system for iOS applications with a developer productivity slant.
Visit [operamhq.com](https://operamhq.com) for details and features.

## Installation

### CocoaPods

Modify your existing `Podfile` to specify the Operam pod:

```ruby
pod 'Operam'
```

Then install the pod by running `pod install`.

### Manually

[Download the Operam SDK](https://downloads.operamhq.com/ios/latest.zip), unzip it, and add the `Operam.framework` file to your Xcode project.

* Open your Xcode project and choose "File -> Add Files to Project_Name..."
* Select the `Operam.framework` file and select the "Copy items if needed" checkbox.
* Select the targets by checking the appropriate checkboxes under the "Add to target" section.
* Add `Operam.framework` to the "Embedded Binaries" list under "General".
* Add a new "Run Script Phase" and set the following command:

```bash
bash "${BUILT_PRODUCTS_DIR}/${FRAMEWORKS_FOLDER_PATH}/Operam.framework/strip-frameworks.sh"
```


## Activating the framework

1. Import the Operam module

    ```swift
    // Swift
    import Operam
    ```
    
    ```objective-c
    // Objective-C
	@import Operam;
    ```

2. Add the following to your app delegate's `application(_:didFinishLaunchingWithOptions:)` method.
	
	```swift
	// Swift
	Operam.start(withAPIKey: "API_KEY")
	```
	```objective-c
	// Objective-C
    [Operam startWithAPIKey:@"API_KEY"];
	```
	Be sure to replace `API_KEY` with your own Operam account API key.
	
## Usage

Build and run your application, then trigger a shake gesture (\^⌘Z in the iOS Simulator, or the real thing on an iOS device) to submit an issue.

Operam also provides a lot of advanced developer features -- refer to the [developer documentation](https://operamhq.com/developers) for all of the details.
