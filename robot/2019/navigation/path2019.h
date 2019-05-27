#ifndef PATH_2019_H
#define PATH_2019_H

// Costs, base 1000.0f is about the cost for one meter in forward direction
#define DEFAULT_NAVIGATION_COST                                               400

// Paths

// TIMING
#define ACCELERATOR_ARM_OFF_ACTION_TIME_TO_ACHIEVE                         0.0f
#define ACCELERATOR_ARM_ON_ACTION_TIME_TO_ACHIEVE                          0.0f

#define GOLDENIUM_PREPARE_TAKE_TIME_TO_ACHIEVE                             0.0f
#define GOLDENIUM_TAKE_TIME_TO_ACHIEVE                                     3.0f

#define GOLDENIUM_PREPARE_DROP_TIME_TO_ACHIEVE                             3.0f
#define GOLDENIUM_DROP_TIME_TO_ACHIEVE                                     3.0f

#define SMALL_DISTRIBUTOR_LINE_1_PREPARE_TIME_TO_ACHIEVE                   0.0f
#define SMALL_DISTRIBUTOR_LINE_1_TAKE_TIME_TO_ACHIEVE                      3.0f
#define SMALL_DISTRIBUTOR_LINE_1_DROP_TIME_TO_ACHIEVE                      3.0f

#define CHAOS_TAKE_TIME_TO_ACHIEVE                                         0.0f
#define CHAOS_DROP_TIME_TO_ACHIEVE                                         0.0f

#define BIG_DISTRIBUTOR_LINE_1_PREPARE_TAKE_TIME_TO_ACHIEVE                0.0f
#define BIG_DISTRIBUTOR_LINE_1_TAKE_TIME_TO_ACHIEVE                        1.0f
#define BIG_DISTRIBUTOR_LINE_2_TAKE_TIME_TO_ACHIEVE                        BIG_DISTRIBUTOR_LINE_1_TAKE_TIME_TO_ACHIEVE
#define BIG_DISTRIBUTOR_LINE_3_TAKE_TIME_TO_ACHIEVE                        BIG_DISTRIBUTOR_LINE_1_TAKE_TIME_TO_ACHIEVE


#define BIG_DISTRIBUTOR_LINE_2_PREPARE_TAKE_TIME_TO_ACHIEVE                0.0f
#define BIG_DISTRIBUTOR_LINE_1_MOVE_TIME_TO_ACHIEVE                        2.0f
#define BIG_DISTRIBUTOR_LINE_2_MOVE_TIME_TO_ACHIEVE                        BIG_DISTRIBUTOR_LINE_1_MOVE_TIME_TO_ACHIEVE
#define BIG_DISTRIBUTOR_LINE_3_MOVE_TIME_TO_ACHIEVE                        BIG_DISTRIBUTOR_LINE_1_MOVE_TIME_TO_ACHIEVE

#define BIG_DISTRIBUTOR_LINE_3_PREPARE_TAKE_TIME_TO_ACHIEVE                0.0f
#define BIG_DISTRIBUTOR_LINE_1_DROP_TIME_TO_ACHIEVE                        1.0f
#define BIG_DISTRIBUTOR_LINE_2_DROP_TIME_TO_ACHIEVE                        BIG_DISTRIBUTOR_LINE_1_DROP_TIME_TO_ACHIEVE
#define BIG_DISTRIBUTOR_LINE_3_DROP_TIME_TO_ACHIEVE                        BIG_DISTRIBUTOR_LINE_1_DROP_TIME_TO_ACHIEVE


#endif
