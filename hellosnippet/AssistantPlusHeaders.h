//
//  AssistantPlusHeaders.h
//  
//
//  Created by Zaid Elkurdi on 3/12/15.
//
//

#import "AssistantHeaders.h"

#ifndef _AssistantPlusHeaders_h
#define _AssistantPlusHeaders_h

@protocol APSiriSession <NSObject>
- (void)sendTextSnippet:(NSString*)text;
- (void)sendAddViews:(NSArray*)views;
-(SOObject*)createSnippet:(NSString*)snippetClass properties:(NSDictionary*)props;
- (void)sendCustomSnippet:(NSString*)snippetClass withProperties:(NSDictionary*)props;
- (void)sendRequestCompleted;
-(SOObject*)createAssistantUtteranceView:(NSString*)text;
-(NSDictionary*)getCurrentLocation;
@end

@protocol APPluginManager <NSObject>
@required
/// Register a command class
-(BOOL)registerCommand:(Class)cls;
/// Register a snippet class
-(BOOL)registerSnippet:(Class)cls;


-(NSString*)localizedString:(NSString*)text;

-(NSString*)systemVersion;
@end

@protocol APPluginSnippet <SiriUIViewController>
@optional
-(id)view;
/// Initializes a snippet by properties
-(id)initWithProperties:(NSDictionary*)props;
/// Initializes a snippet by properties and system
-(id)initWithProperties:(NSDictionary*)props system:(id<APPluginManager>)system;
/// Returns a view representing snippet, can be self if the conforming class is already UIView

@end


/** Protocol specifying methods of an extension class handling commands.
 Classes conforming to this protocol are initialized just after loading bundle and will remain in memory.
 Don't forget you really should prefix your class with some shortcut, e.g. K3AAwesomeCommand!
 */
@protocol APPluginCommand <NSObject>
@optional

-(BOOL)handleSpeech:(NSString*)text session:(id<APSiriSession>)session;
-(id)initWithSystem:(id<APPluginManager>)manager;

-(void)assistantDismissed;

@end


/// Protocol specifying methods of the extension's principal class
@protocol APPlugin <NSObject>

@required
/// The first method which is called on your class, system is where you register commands and snippets
-(id)initWithSystem:(id<APPluginManager>)system;

@optional

-(void)assistantDismissed; //clean up

@end

#endif
