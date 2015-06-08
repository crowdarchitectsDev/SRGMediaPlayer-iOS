//
//  Copyright (c) RTS. All rights reserved.
//
//  Licence information is available from the LICENCE file.
//

#import <CoreMedia/CoreMedia.h>
#import <RTSMediaPlayer/RTSMediaSegmentsDataSource.h>
#import <UIKit/UIKit.h>

@class RTSMediaSegmentsController;
@class RTSMediaPlayerController;

@protocol RTSTimelineViewDelegate;

/**
 *  A view displaying segments associated with a stream as a linear collection of cells
 *
 *  To add a timeline to a custom player layout, simply drag and drop an RTSTimelineView onto the player layout,
 *  and bind its segment controller and delegate outlets. You can of course instantiate and configure the view 
 *  programatically as well. Then call -reloadSegmentsWithIdentifier: when you need to retrieve segments from the 
 *  controller
 *
 *  Customisation of timeline cells is achieved through subclassing of UICollectionViewCell, exactly like a usual 
 *  UICollectionView
 */
@interface RTSTimelineView : UIView <UICollectionViewDataSource, UICollectionViewDelegate>

/**
 *  The controller which provides segments to the timeline
 */
@property (nonatomic, weak) IBOutlet RTSMediaSegmentsController *segmentsController;

/**
 *  The timeline delegate
 */
@property (nonatomic, weak) IBOutlet id<RTSTimelineViewDelegate> delegate;

/**
 *  The width of cells within the timeline. Defaults to 60
 */
@property (nonatomic) IBInspectable CGFloat itemWidth;

/**
 * The spacing between cells in the timeline. Defaults to 4
 */
@property (nonatomic) IBInspectable CGFloat itemSpacing;

/**
 *  Register cell classes for reuse. Cells must be subclasses of UICollectionViewCell and can be instantiated either
 *  programmatically or using a nib. For more information about cell reuse, refer to UICollectionView documentation
 */
- (void)registerClass:(Class)cellClass forCellWithReuseIdentifier:(NSString *)identifier;
- (void)registerNib:(UINib *)nib forCellWithReuseIdentifier:(NSString *)identifier;

/**
 *  Call this method to trigger a reload of the segments from the data source
 */
- (void)reloadSegmentsForIdentifier:(NSString *)identifier;

/**
 *  Dequeue a reusable cell for a given segment
 *
 *  @param identifier The cell identifier (must be appropriately set for the cell)
 *  @param segment    The segment for which a cell must be dequeued
 */
- (id)dequeueReusableCellWithReuseIdentifier:(NSString *)identifier forSegment:(id<RTSMediaSegment>)segment;

- (NSArray *)visibleCells;

/**
 *  Scroll to make the specified segment visible (does nothing if the segment does not belong to the displayed segments)
 */
- (void)scrollToSegment:(id<RTSMediaSegment>)segment animated:(BOOL)animated;

/**
 *  Scroll to make the segment to which the specified time belongs visible (does nothing if the time does not match
 *  any segment)
 */
- (void)scrollToSegmentAtTime:(CMTime)time animated:(BOOL)animated;

@end

/**
 *  Timeline delegate protocol
 */
@protocol RTSTimelineViewDelegate <NSObject>

/**
 *  Return the cell to be displayed for a segment. You should call -dequeueReusableCellWithReuseIdentifier:forSegment:
 *  within the implementation of this method to reuse existing cells and improve scrolling smoothness
 *
 *  @param timelineView The timeline
 *  @param segment      The segment for which the cell must be returned
 *
 *  @return The cell to use
 */
- (UICollectionViewCell *)timelineView:(RTSTimelineView *)timelineView cellForSegment:(id<RTSMediaSegment>)segment;


@end
