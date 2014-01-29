#import "CMPFormatDescription+Text.h"


OSStatus CMP3GTextFormatDescriptionCreate(CFAllocatorRef allocator, CMFormatDescriptionRef *outFormatDescription)
{
	return CMPTextFormatDescriptionCreate(allocator, kCMTextFormatType_3GText, outFormatDescription);
}

OSStatus CMPQTTextFormatDescriptionCreate(CFAllocatorRef allocator, CMFormatDescriptionRef *outFormatDescription)
{
	return CMPTextFormatDescriptionCreate(allocator, kCMTextFormatType_QTText, outFormatDescription);
}

OSStatus CMPTextFormatDescriptionCreate(CFAllocatorRef allocator, CMTextFormatType subtype, CMFormatDescriptionRef *outFormatDescription)
{
#if 0
	// Obj-C extensions
	NSDictionary *extensions = @{
		(id)kCMTextFormatDescriptionExtension_DisplayFlags : @(0),
		(id)kCMTextFormatDescriptionExtension_BackgroundColor : @{
			(id)kCMTextFormatDescriptionColor_Red : @0,
			(id)kCMTextFormatDescriptionColor_Green : @0,
			(id)kCMTextFormatDescriptionColor_Blue : @0,
			(id)kCMTextFormatDescriptionColor_Alpha : @255
		},
		(id)kCMTextFormatDescriptionExtension_DefaultTextBox : @{
			(id)kCMTextFormatDescriptionRect_Top : @0,
			(id)kCMTextFormatDescriptionRect_Left : @0,
			(id)kCMTextFormatDescriptionRect_Bottom : @0,
			(id)kCMTextFormatDescriptionRect_Right : @0
		},
		(id)kCMTextFormatDescriptionExtension_DefaultStyle : @{
			(id)kCMTextFormatDescriptionStyle_StartChar : @0,
			(id)kCMTextFormatDescriptionStyle_EndChar : @0,
			(id)kCMTextFormatDescriptionStyle_Font : @1,
			(id)kCMTextFormatDescriptionStyle_FontFace : @0,
			(id)kCMTextFormatDescriptionStyle_ForegroundColor : @{
				(id)kCMTextFormatDescriptionColor_Red : @255,
				(id)kCMTextFormatDescriptionColor_Green : @255,
				(id)kCMTextFormatDescriptionColor_Blue : @255,
				(id)kCMTextFormatDescriptionColor_Alpha : @255
			},
			(id)kCMTextFormatDescriptionStyle_FontSize : @255
		},
		(id)kCMTextFormatDescriptionExtension_HorizontalJustification : @0,
		(id)kCMTextFormatDescriptionExtension_VerticalJustification : @0,
		(id)kCMTextFormatDescriptionExtension_FontTable : @{
			@"1" : @"Sans-Serif"
		}
	};
#endif
	
	const SInt8 value0 = 0;
	CFNumberRef number0 = CFNumberCreate(allocator, kCFNumberSInt8Type, &value0);

	const SInt8 value1 = 1;
	CFNumberRef number1 = CFNumberCreate(allocator, kCFNumberSInt8Type, &value1);

	const SInt8 value255 = 255;
	CFNumberRef number255 = CFNumberCreate(allocator, kCFNumberSInt8Type, &value255);

	// background color
	
	const void *backgroundColorKeys[4] = {
		kCMTextFormatDescriptionColor_Red,
		kCMTextFormatDescriptionColor_Green,
		kCMTextFormatDescriptionColor_Blue,
		kCMTextFormatDescriptionColor_Alpha,
	};
	
	const void *backgroundColorValues[4] = {
		number0,
		number0,
		number0,
		number255,
	};
	
	CFDictionaryRef backgroundColor = CFDictionaryCreate(allocator, backgroundColorKeys, backgroundColorValues, 4, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
	
	//  default text box
	
	const void *defaultTextBoxKeys[4] = {
		kCMTextFormatDescriptionRect_Top,
		kCMTextFormatDescriptionRect_Left,
		kCMTextFormatDescriptionRect_Bottom,
		kCMTextFormatDescriptionRect_Right,
	};
	
	const void *defaultTextBoxValues[4] = {
		number0,
		number0,
		number0,
		number0,
	};
	
	CFDictionaryRef defaultTextBox = CFDictionaryCreate(allocator, defaultTextBoxKeys, defaultTextBoxValues, 4, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
	
	// foreground color
	
	const void *foregroundColorKeys[4] = {
		kCMTextFormatDescriptionColor_Red,
		kCMTextFormatDescriptionColor_Green,
		kCMTextFormatDescriptionColor_Blue,
		kCMTextFormatDescriptionColor_Alpha,
	};
	
	const void *foregroundColorValues[4] = {
		number255,
		number255,
		number255,
		number255,
	};
	
	CFDictionaryRef foregroundColor = CFDictionaryCreate(allocator, foregroundColorKeys, foregroundColorValues, 4, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
	
	// default style
	
	const void *defaultStyleKeys[6] = {
		kCMTextFormatDescriptionStyle_StartChar,
		kCMTextFormatDescriptionStyle_EndChar,
		kCMTextFormatDescriptionStyle_Font,
		kCMTextFormatDescriptionStyle_FontFace,
		kCMTextFormatDescriptionStyle_FontSize,
		kCMTextFormatDescriptionStyle_ForegroundColor,
	};
	
	const void *defaultStyleValues[6] = {
		number0,
		number0,
		number1,
		number0,
		number255,
		foregroundColor,
	};
	
	CFDictionaryRef defaultStyle = CFDictionaryCreate(allocator, defaultStyleKeys, defaultStyleValues, 6, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
	
	// font table
	
	const void *fontTableKeys[1] = {
		CFSTR("1"),
	};
	
	const void *fontTableValues[1] = {
		CFSTR("Sans-Serif"),
	};
	
	CFDictionaryRef fontTable = CFDictionaryCreate(allocator, fontTableKeys, fontTableValues, 1, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
	
	// extensions
	
	const void *extensionsKeys[7] = {
		kCMTextFormatDescriptionExtension_DisplayFlags,
		kCMTextFormatDescriptionExtension_BackgroundColor,
		kCMTextFormatDescriptionExtension_DefaultTextBox,
		kCMTextFormatDescriptionExtension_DefaultStyle,
		kCMTextFormatDescriptionExtension_HorizontalJustification,
		kCMTextFormatDescriptionExtension_VerticalJustification,
		kCMTextFormatDescriptionExtension_FontTable,
	};
	
	const void *extensionsValues[7] = {
		number0,
		backgroundColor,
		defaultTextBox,
		defaultStyle,
		number0,
		number0,
		fontTable,
	};
	
	CFDictionaryRef extensions = CFDictionaryCreate(allocator, extensionsKeys, extensionsValues, 7, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
	
	OSStatus status = CMFormatDescriptionCreate(allocator, kCMMediaType_Text, subtype, extensions, outFormatDescription);
	
	CFRelease(extensions);
	
	CFRelease(backgroundColor);
	CFRelease(defaultTextBox);
	CFRelease(foregroundColor);
	CFRelease(defaultStyle);
	CFRelease(fontTable);
	
	CFRelease(number0);
	CFRelease(number1);
	CFRelease(number255);
	
	return status;
}

