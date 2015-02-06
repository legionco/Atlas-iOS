//
//  LYRUIParticipantPickerController.h
//  
//
//  Created by Kevin Coleman on 8/29/14.
//
//

#import <UIKit/UIKit.h>
#import "LYRUIParticipantTableViewCell.h"
#import "LYRUIParticipant.h"
#import "LYRUIParticipantTableViewController.h"

@class LYRUIParticipantPickerController;

/**
 @abstract The `LYRUIParticipantPickerControllerDelegate` protocol must be adopted by objects that wish to act
 as the delegate for a `LYRUIParticipantPickerController` object.
 */
@protocol LYRUIParticipantPickerControllerDelegate <NSObject>

/**
 @abstract Tells the receiver that the participant picker was dismissed without making a selection.
 @param participantPickerController The participant picker that was dismissed.
 */
- (void)participantPickerControllerDidCancel:(LYRUIParticipantPickerController *)participantPickerController;

/**
 @abstract Tells the receiver that the user has selected a participant from a participant picker.
 @param participantPickerController The participant picker in which the selection was made.
 @param participant The participant who was selected.
 */
- (void)participantPickerController:(LYRUIParticipantPickerController *)participantPickerController didSelectParticipant:(id<LYRUIParticipant>)participant;

@optional

/**
 @abstract Tells the receiver that the user has deselected a participant from a participant picker.
 @param participantPickerController The participant picker in which the deselection was made.
 @param participant The participant who was deselected.
 */
- (void)participantPickerController:(LYRUIParticipantPickerController *)participantPickerController didDeselectParticipant:(id<LYRUIParticipant>)participant;

@end

/**
 @abstract Objects wishing to act as the data source for a participant picker must adopt the `LYRUIParticipantsPickerDataSource` protocol.
 */
@protocol LYRUIParticipantPickerDataSource <NSObject>

/**
 @abstract The set of participants to be presented in the picker. Each object in the returned collection must conform to the `LYRUIParticipant` protocol.
 @discussion The picker presents the returned participants in alphabetical order according to `sortType` and sectioned by the corresponding first initial.
 */
- (NSSet *)participantsForParticipantPickerController:(LYRUIParticipantPickerController *)participantPickerController;

/**
 @abstract Asynchronously searches for participants that match the given search text.
 @discussion Invoked by the participant picker controller when the user inputs text into the search bar. The receiver is
 to perform the search, build a set of matching participants, and then call the completion block. The controller will section
 the participants and present them in alphabetical order according to the value returned by the `sortType` property.
 */
- (void)participantPickerController:(LYRUIParticipantPickerController *)participantPickerController searchForParticipantsMatchingText:(NSString *)searchText completion:(void (^)(NSSet *participants))completion;

@end

/**
 @abstract Displays a list of participants in a navigation controller and allows for searching of participants.
 */
@interface LYRUIParticipantPickerController : UINavigationController

///------------------------------------
/// @name Creating a Participant Picker
///------------------------------------

/**
 @abstract Creates and returns a participant picker initialized with the given set of participants.
 @param dataSource The object to acts as the picker's data source.
 @param sortType The sort type to use for the participants.
 @returns A new participant picker initialized with the given data source and sort type.
 */
+ (instancetype)participantPickerWithDataSource:(id<LYRUIParticipantPickerDataSource>)dataSource sortType:(LYRUIParticipantPickerSortType)sortType;

///----------------------------------------
/// @name Accessing the Set of Participants
///----------------------------------------

@property (nonatomic) LYRUIParticipantPickerSortType sortType;

///-----------------------------------------
/// @name Accessing the Picker Data Source
///-----------------------------------------

@property (nonatomic, weak) id<LYRUIParticipantPickerDataSource> dataSource;

///-----------------------------------------
/// @name Accessing the Picker Delegate
///-----------------------------------------

@property (nonatomic, weak) id<LYRUIParticipantPickerControllerDelegate> participantPickerDelegate;

///---------------------------------
/// @name Configuring Picker Options
///---------------------------------

/**
 @abstract A boolean value that determines whether multiple participants can be selected at once.
 @discussion The defauly value of this property is `YES`.
 @raises NSInternalInconsistencyException Raised if the value is mutated after the receiver has been presented.
 */
@property (nonatomic, assign) BOOL allowsMultipleSelection;

/**
 @abstract The table view cell class for customizing the display of participants.
 @default `[LYRUIParticipantTableViewCell class]`
 @raises NSInternalInconsistencyException Raised if the value is mutated after the receiver has been presented.
 */
@property (nonatomic) Class<LYRUIParticipantPresenting> cellClass;

/**
 @abstract Configures the height of each row in the receiver.
 @default 40.0f
 @raises NSInternalInconsistencyException Raised if the value is mutated after the receiver has been presented.
 */
@property (nonatomic, assign) CGFloat rowHeight;

/**
 @abstract Configures the sort type of the receiver.
 @default LYRUIParticipantPickerSortTypeFirstName
 @raises NSInternalInconsistencyException Raised if the value is mutated after the receiver has been presented.
 */
@property (nonatomic, assign) LYRUIParticipantPickerSortType participantPickerSortType;

@end