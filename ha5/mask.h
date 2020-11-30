#ifndef __MASK_H__
#define __MASK_H__

#include <vector>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/core.hpp>

namespace Mask {

const std::vector<cv::Rect> mask = {
	cv::Rect(207, 37, 26, 35),
	cv::Rect(234, 37, 25, 35),
	cv::Rect(260, 37, 25, 35),
	cv::Rect(314, 37, 24, 37),
	cv::Rect(345, 37, 26, 37),
	cv::Rect(379, 38, 24, 36),
	cv::Rect(410, 38, 25, 35),
	cv::Rect(442, 37, 27, 34),
	cv::Rect(474, 38, 25, 32),
	cv::Rect(507, 39, 22, 31),
	cv::Rect(540, 38, 21, 31),
	cv::Rect(571, 38, 21, 32),
	cv::Rect(234, 77, 24, 36),
	cv::Rect(263, 77, 22, 36),
	cv::Rect(289, 77, 24, 36),
	cv::Rect(316, 77, 24, 36),
	cv::Rect(344, 79, 23, 34),
	cv::Rect(371, 77, 23, 36),
	cv::Rect(425, 80, 21, 32),
	cv::Rect(454, 80, 19, 31),
	cv::Rect(479, 81, 22, 31),
	cv::Rect(506, 81, 21, 31),
	cv::Rect(533, 82, 20, 30),
	cv::Rect(560, 79, 22, 33),
	cv::Rect(237, 120, 22, 36),
	cv::Rect(266, 120, 15, 36),
	cv::Rect(208, 163, 24, 34),
	cv::Rect(235, 164, 22, 32),
	cv::Rect(262, 164, 22, 32),
	cv::Rect(292, 164, 15, 32),
	cv::Rect(317, 163, 22, 33),
	cv::Rect(426, 163, 14, 33),
	cv::Rect(208, 205, 23, 32),
	cv::Rect(265, 205, 14, 32),
	cv::Rect(290, 206, 22, 31),
	cv::Rect(317, 205, 22, 32),
	cv::Rect(347, 355, 13, -113),
	cv::Rect(369, 205, 24, 32),
	cv::Rect(479, 207, 21, 30),
	cv::Rect(506, 206, 19, 30),
	cv::Rect(533, 206, 22, 30),
	cv::Rect(561, 206, 19, 30),
	cv::Rect(615, 205, 20, 31),
	cv::Rect(641, 205, 19, 32),
	cv::Rect(207, 247, 24, 32),
	cv::Rect(236, 247, 17, 32),
	cv::Rect(267, 270, 9, 11),
	cv::Rect(289, 247, 22, 32),
	cv::Rect(317, 247, -89, 32),
	cv::Rect(343, 351, 22, -73),
	cv::Rect(371, 247, 21, 32),
	cv::Rect(400, 248, 15, 30),
	cv::Rect(197, 561, 79, 79),
	cv::Rect(276, 589, 9, 21),
	cv::Rect(263, 623, 23, 39),
	cv::Rect(369, 581, 23, 31),
	cv::Rect(402, 605, 14, 13),
	cv::Rect(423, 581, 23, 31),
	cv::Rect(453, 581, 19, 31),
	cv::Rect(479, 581, 20, 31),
	cv::Rect(506, 585, 22, 27),
	cv::Rect(532, 585, 22, 27),
	cv::Rect(343, 634, 26, 11),
	cv::Rect(371, 622, 23, 33),
	cv::Rect(402, 647, 13, 13),
	cv::Rect(427, 623, 15, 31),
	cv::Rect(454, 623, 20, 31),
	cv::Rect(481, 629, 19, 25),
	cv::Rect(505, 632, 25, 20),
	cv::Rect(532, 629, 24, 25),
	cv::Rect(858, 17, 22, 16),
	cv::Rect(894, 17, 23, 16),
	cv::Rect(778, 39, 18, 30),
	cv::Rect(801, 41, 23, 25),
	cv::Rect(831, 39, 15, 31),
	cv::Rect(856, 38, 22, 32),
	cv::Rect(890, 45, 11, 28),
	cv::Rect(909, 39, 23, 31),
	cv::Rect(937, 39, 22, 31),
	cv::Rect(971, 46, 11, 27),
	cv::Rect(990, 38, 24, 32),
	cv::Rect(1018, 38, 23, 32),
	cv::Rect(697, 80, 20, 31),
	cv::Rect(724, 80, 19, 32),
	cv::Rect(750, 80, 21, 31),
	cv::Rect(805, 80, 20, 32),
	cv::Rect(830, 80, 22, 32),
	cv::Rect(857, 81, 22, 31),
	cv::Rect(913, 81, 16, 31),
	cv::Rect(938, 81, 23, 31),
	cv::Rect(965, 81, 23, 31),
	cv::Rect(992, 81, 23, 31),
	cv::Rect(831, 128, 22, 25),
	cv::Rect(858, 128, 22, 25),
	cv::Rect(913, 123, 21, 30),
	cv::Rect(944, 147, 12, 12),
	cv::Rect(965, 123, 23, 30),
	cv::Rect(993, 123, 21, 30),
	cv::Rect(1020, 123, 22, 30),
	cv::Rect(1047, 122, 24, 35),
	cv::Rect(831, 171, 20, 23),
	cv::Rect(858, 170, 19, 24),
	cv::Rect(912, 164, 21, 31),
	cv::Rect(943, 189, 12, 11),
	cv::Rect(965, 164, 22, 32),
	cv::Rect(992, 164, 22, 31),
	cv::Rect(1019, 164, 23, 31),
	cv::Rect(1046, 164, 24, 35),
	cv::Rect(831, 211, 21, 25),
	cv::Rect(857, 211, 22, 25),
	cv::Rect(912, 206, 21, 30),
	cv::Rect(944, 231, 11, 11),
	cv::Rect(965, 206, 23, 30),
	cv::Rect(992, 206, 23, 30),
	cv::Rect(1019, 205, 23, 31),
	cv::Rect(1045, 206, 26, 34),
	cv::Rect(884, 247, 22, 32),
	cv::Rect(911, 247, 22, 32),
	cv::Rect(939, 247, 21, 32),
	cv::Rect(965, 247, 22, 32),
	cv::Rect(1021, 247, 15, 32),
	cv::Rect(856, 294, 22, 35),
	cv::Rect(938, 289, 22, 31),
	cv::Rect(969, 313, 12, 14),
	cv::Rect(991, 289, 23, 31),
	cv::Rect(1019, 289, 22, 31),
	cv::Rect(1048, 291, 20, 17),
	cv::Rect(857, 336, 21, 32),
	cv::Rect(937, 331, 22, 30),
	cv::Rect(970, 356, 11, 10),
	cv::Rect(991, 331, 22, 30),
	cv::Rect(1018, 331, 22, 30),
	cv::Rect(1047, 333, 19, 17),
	cv::Rect(856, 373, 24, 31),
	cv::Rect(910, 385, 25, 9),
	cv::Rect(937, 373, 22, 30),
	cv::Rect(969, 397, 12, 12),
	cv::Rect(991, 373, 22, 30),
	cv::Rect(1018, 373, 22, 30),
	cv::Rect(1047, 376, 19, 16),
	cv::Rect(831, 420, 20, 32),
	cv::Rect(857, 419, 21, 26),
	cv::Rect(911, 426, 24, 10),
	cv::Rect(938, 414, 22, 31),
	cv::Rect(970, 439, 12, 12),
	cv::Rect(994, 414, 14, 31),
	cv::Rect(1019, 414, 22, 31),
	cv::Rect(1048, 416, 19, 18),
	cv::Rect(831, 457, 22, 30),
	cv::Rect(859, 461, 20, 25),
	cv::Rect(938, 456, 22, 31),
	cv::Rect(970, 480, 12, 12),
	cv::Rect(992, 456, 22, 31),
	cv::Rect(1019, 456, 22, 31),
	cv::Rect(1049, 458, 19, 17),
	cv::Rect(832, 506, 20, 29),
	cv::Rect(912, 499, 21, 29),
	cv::Rect(944, 522, 11, 12),
	cv::Rect(965, 498, 22, 30),
	cv::Rect(992, 498, 22, 31),
	cv::Rect(1019, 498, 22, 30),
	cv::Rect(833, 540, 19, 36),
	cv::Rect(912, 552, 24, 9),
	cv::Rect(939, 539, 21, 31),
	cv::Rect(970, 564, 13, 11),
	cv::Rect(996, 539, 13, 31),
	cv::Rect(1020, 539, 22, 31),
	cv::Rect(614, 582, 20, 30),
	cv::Rect(641, 586, 21, 26),
	cv::Rect(668, 594, 24, 8),
	cv::Rect(695, 582, 20, 29),
	cv::Rect(728, 608, 10, 9),
	cv::Rect(749, 582, 21, 30),
	cv::Rect(777, 582, 19, 30),
	cv::Rect(803, 582, 21, 30),
	cv::Rect(858, 593, 22, 9),
	cv::Rect(884, 582, 22, 30),
	cv::Rect(917, 606, 11, 11),
	cv::Rect(938, 581, 22, 31),
	cv::Rect(968, 582, 14, 30),
	cv::Rect(992, 581, 22, 31),
	cv::Rect(614, 623, 20, 31),
	cv::Rect(641, 628, 23, 26),
	cv::Rect(668, 635, 24, 9),
	cv::Rect(696, 624, 19, 30),
	cv::Rect(730, 648, 10, 9),
	cv::Rect(750, 624, 20, 30),
	cv::Rect(777, 624, 22, 30),
	cv::Rect(804, 624, 20, 30),
	cv::Rect(859, 636, 23, 8),
	cv::Rect(886, 623, 21, 31),
	cv::Rect(916, 647, 12, 12),
	cv::Rect(939, 623, 21, 31),
	cv::Rect(966, 623, 22, 31),
	cv::Rect(994, 623, 21, 31),
	cv::Rect(628, 0, 11, 712),
	cv::Rect(0, 359, 1164, 12),
	cv::Rect(315, 247, 25, 32),
	cv::Rect(342, 247, 25, 32),
	cv::Rect(347, 230, 13, 11),
	cv::Rect(505, 247, 23, 32),
	cv::Rect(532, 247, 22, 32),
	cv::Rect(563, 247, 19, 32),
	cv::Rect(615, 247, 23, 32),
	cv::Rect(642, 247, 21, 32),
	cv::Rect(670, 247, 19, 32),
	cv::Rect(615, 123, 22, 29),
	cv::Rect(643, 125, 19, 27),
	cv::Rect(668, 123, 21, 29),
	cv::Rect(697, 125, 19, 27),
	cv::Rect(750, 124, 20, 28),
	cv::Rect(777, 123, 20, 29),
	cv::Rect(807, 128, 18, 23),
	cv::Rect(615, 664, 19, 31),
	cv::Rect(641, 664, 20, 31),
	cv::Rect(675, 672, 8, 23),
	cv::Rect(723, 664, 20, 31),
	cv::Rect(750, 665, 19, 30),
	cv::Rect(803, 665, 20, 30),
	cv::Rect(833, 664, 15, 31),
	cv::Rect(856, 665, 22, 31),
	cv::Rect(885, 664, 21, 31),
	cv::Rect(911, 665, 22, 30),
	cv::Rect(940, 664, 20, 31),
	cv::Rect(965, 664, 22, 31),
	cv::Rect(993, 665, 21, 31),
	cv::Rect(749, 426, 22, 9),
	cv::Rect(776, 415, 17, 30),
	cv::Rect(884, 176, 23, 9),
	cv::Rect(804, 218, 23, 8),
	cv::Rect(911, 302, 24, 8),
	cv::Rect(887, 136, 21, 7),
	cv::Rect(750, 510, 22, 9),
	cv::Rect(776, 498, 21, 31),
	cv::Rect(804, 177, 20, 7),
	cv::Rect(912, 469, 21, 7),
	cv::Rect(911, 343, 23, 9),
	cv::Rect(751, 336, 21, 21),
	cv::Rect(778, 333, 19, 24),
	cv::Rect(0, 7, 1121, 14)
};

void makeMask(cv::Mat& image);
size_t removeMaskFeatures(std::vector<cv::KeyPoint>& image);

}

#endif
