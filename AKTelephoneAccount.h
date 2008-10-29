//
//  AKTelephoneAccount.h
//  Telephone
//
//  Created by Alexei Kuznetsov on 17.06.08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <pjsua-lib/pjsua.h>


@class AKTelephoneCall;

// Keys for AKTelephoneAccount properties
APPKIT_EXTERN NSString *AKTelephoneAccountFullName;
APPKIT_EXTERN NSString *AKTelephoneAccountSIPAddress;
APPKIT_EXTERN NSString *AKTelephoneAccountRegistrar;
APPKIT_EXTERN NSString *AKTelephoneAccountRealm;
APPKIT_EXTERN NSString *AKTelephoneAccountUsername;

@interface AKTelephoneAccount : NSObject {
	id delegate;
	
	NSString *fullName;
	NSString *sipAddress;
	NSString *registrar;
	NSString *realm;
	NSString *username;
	
	NSNumber *identifier;
	
	NSMutableArray *calls;
}

@property(readwrite, assign) id delegate;
@property(readwrite, copy) NSString *fullName;
@property(readwrite, copy) NSString *sipAddress;
@property(readwrite, copy) NSString *registrar;
@property(readwrite, copy) NSString *realm;
@property(readwrite, copy) NSString *username;
@property(readwrite, copy) NSNumber *identifier;
@property(readwrite, assign, getter=isRegistered) BOOL registered;
@property(readonly, copy) NSNumber *registrationStatus;
@property(readonly, copy) NSString *registrationStatusText;
@property(readonly, copy) NSNumber *registrationExpireTime;
@property(readwrite, assign, getter=isOnline) BOOL online;
@property(readonly, copy) NSString *onlineStatusText;
@property(readonly, retain) NSMutableArray *calls;

+ (id)telephoneAccountWithFullName:(NSString *)aFullName
						sipAddress:(NSString *)aSIPAddress
						 registrar:(NSString *)aRegistrar
							 realm:(NSString *)aRealm
						  username:(NSString *)aUsername;

- (id)initWithFullName:(NSString *)aFullName
			sipAddress:(NSString *)aSIPAddress
			 registrar:(NSString *)aRegistrar
				 realm:(NSString *)aRealm
			  username:(NSString *)aUsername;

- (AKTelephoneCall *)makeCallTo:(NSString *)destinationURI;
- (BOOL)unregister;

@end

// Callback from PJSUA
void AKTelephoneAccountRegistrationStateChanged(pjsua_acc_id accountIdentifier);


@interface NSObject(AKTelephoneAccountNotifications)
- (void)telephoneAccountRegistrationDidChange:(NSNotification *)notification;
@end

@interface NSObject(AKTelephoneAccountDelegate)
- (void)telephoneAccount:(AKTelephoneAccount *)sender didReceiveCall:(AKTelephoneCall *)aCall;
@end

// Notifications
APPKIT_EXTERN NSString *AKTelephoneAccountRegistrationDidChangeNotification;