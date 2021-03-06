//
//  GMSAutocompleteViewController.h
//  Google Maps SDK for iOS
//
//  Copyright 2015 Google Inc.
//
//  Usage of this SDK is subject to the Google Maps/Google Earth APIs Terms of
//  Service: https://developers.google.com/maps/terms
//

#import <UIKit/UIKit.h>

#import <GoogleMaps/GMSCoordinateBounds.h>
#import <GoogleMaps/GMSAutocompleteFilter.h>
#import <GoogleMaps/GMSAutocompletePrediction.h>
#import <GoogleMaps/GMSPlace.h>

@class GMSAutocompleteViewController;

/**
 * Protocol used by |GMSAutocompleteViewController|, to communicate the user's interaction
 * with the controller to the application.
 */
@protocol GMSAutocompleteViewControllerDelegate <NSObject>

@required

/**
 * Called when a place has been selected from the available autocomplete predictions.
 * @param viewController The |GMSAutocompleteViewController| that generated the event.
 * @param place The |GMSPlace| that was returned.
 */
- (void)viewController:(GMSAutocompleteViewController *)viewController
    didAutocompleteWithPlace:(GMSPlace *)place;

/**
 * Called when a non-retryable error occurred when retrieving autocomplete predictions or place
 * details. A non-retryable error is defined as one that is unlikely to be fixed by immediately
 * retrying the operation.
 * <p>
 * Only the following values of |GMSPlacesErrorCode| are retryable:
 * <ul>
 * <li>kGMSPlacesNetworkError
 * <li>kGMSPlacesServerError
 * <li>kGMSPlacesInternalError
 * </ul>
 * All other error codes are non-retryable.
 * @param viewController The |GMSAutocompleteViewController| that generated the event.
 * @param error The |NSError| that was returned.
 */
- (void)viewController:(GMSAutocompleteViewController *)viewController
    didFailAutocompleteWithError:(NSError *)error;

/**
 * Called when the user taps the Cancel button in a |GMSAutocompleteViewController|.
 * @param viewController The |GMSAutocompleteViewController| that generated the event.
 */
- (void)wasCancelled:(GMSAutocompleteViewController *)viewController;

@optional

/**
 * Called when the user selects an autocomplete prediction from the list but before requesting
 * place details. Returning NO from this method will suppress the place details fetch and
 * didAutocompleteWithPlace will not be called.
 * @param viewController The |GMSAutocompleteViewController| that generated the event.
 * @param prediction The |GMSAutocompletePrediction| that was selected.
 */
- (BOOL)viewController:(GMSAutocompleteViewController *)viewController
   didSelectPrediction:(GMSAutocompletePrediction *)prediction;

/**
 * Called once every time new autocomplete predictions are received.
 * @param viewController The |GMSAutocompleteViewController| that generated the event.
 */
- (void)didUpdateAutocompletePredictions:(GMSAutocompleteViewController *)viewController;

/**
 * @param viewController The |GMSAutocompleteViewController| that generated the event.
 * Called once immediately after a request for autocomplete predictions is made.
 */
- (void)didRequestAutocompletePredictions:(GMSAutocompleteViewController *)viewController;

@end


/**
 * GMSAutocompleteViewController provides an interface that displays a table of autocomplete
 * predictions that updates as the user enters text. Place selections made by the user are
 * returned to the app via the |GMSAutocompleteViewControllerResultsDelegate| protocol.
 *
 * To use GMSAutocompleteViewController, set its delegate to an object in your app that
 * implements the |GMSAutocompleteViewControllerDelegate| protocol and present the controller
 * (eg using presentViewController). The |GMSAutocompleteViewControllerDelegate| delegate methods
 * can be used to determine when the user has selected a place or has cancelled selection.
 */
@interface GMSAutocompleteViewController : UIViewController

/** Delegate to be notified when a place is selected or picking is cancelled. */
@property(nonatomic, weak) IBOutlet id<GMSAutocompleteViewControllerDelegate> delegate;

/** Bounds used to bias the autocomplete search (can be nil). */
@property(nonatomic, strong) GMSCoordinateBounds *autocompleteBounds;

/** Filter to apply to autocomplete suggestions (can be nil). */
@property(nonatomic, strong) GMSAutocompleteFilter *autocompleteFilter;

@end


