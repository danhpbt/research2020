# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
		simplecam

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
		image_util.cpp

		source/BasicEffect.cpp
		source/BokehEffect.cpp
		source/ConvMatrix.cpp

		# libyuv
		libyuv/source/compare.cc
		libyuv/source/compare_common.cc
		libyuv/source/compare_gcc.cc
		libyuv/source/compare_mmi.cc
		libyuv/source/compare_msa.cc
		libyuv/source/compare_neon.cc
		libyuv/source/compare_neon64.cc
		libyuv/source/compare_win.cc
		libyuv/source/convert.cc
		libyuv/source/convert_argb.cc
		libyuv/source/convert_from.cc
		libyuv/source/convert_from_argb.cc
		libyuv/source/convert_jpeg.cc
		libyuv/source/convert_to_argb.cc
		libyuv/source/convert_to_i420.cc
		libyuv/source/cpu_id.cc
		libyuv/source/mjpeg_decoder.cc
		libyuv/source/mjpeg_validate.cc
		libyuv/source/planar_functions.cc
		libyuv/source/rotate.cc
		libyuv/source/rotate_any.cc
		libyuv/source/rotate_argb.cc
		libyuv/source/rotate_common.cc
		libyuv/source/rotate_gcc.cc
		libyuv/source/rotate_mmi.cc
		libyuv/source/rotate_msa.cc
		libyuv/source/rotate_neon.cc
		libyuv/source/rotate_neon64.cc
		libyuv/source/rotate_win.cc
		libyuv/source/row_any.cc
		libyuv/source/row_common.cc
		libyuv/source/row_gcc.cc
		libyuv/source/row_mmi.cc
		libyuv/source/row_msa.cc
		libyuv/source/row_neon.cc
		libyuv/source/row_neon64.cc
		libyuv/source/row_win.cc
		libyuv/source/scale.cc
		libyuv/source/scale_any.cc
		libyuv/source/scale_argb.cc
		libyuv/source/scale_common.cc
		libyuv/source/scale_gcc.cc
		libyuv/source/scale_mmi.cc
		libyuv/source/scale_msa.cc
		libyuv/source/scale_neon.cc
		libyuv/source/scale_neon64.cc
		libyuv/source/scale_win.cc
		libyuv/source/video_common.cc

		# Agg2D
		Agg2D/src/Agg2D.cpp
		Agg2D/src/Agg2D/agg_arc.cpp
		Agg2D/src/Agg2D/agg_arrowhead.cpp
		Agg2D/src/Agg2D/agg_bezier_arc.cpp
		Agg2D/src/Agg2D/agg_bspline.cpp
		Agg2D/src/Agg2D/agg_curves.cpp
		Agg2D/src/Agg2D/agg_embedded_raster_fonts.cpp
		Agg2D/src/Agg2D/agg_gsv_text.cpp
		Agg2D/src/Agg2D/agg_image_filters.cpp
		Agg2D/src/Agg2D/agg_line_aa_basics.cpp
		Agg2D/src/Agg2D/agg_line_profile_aa.cpp
		Agg2D/src/Agg2D/agg_rounded_rect.cpp
		Agg2D/src/Agg2D/agg_sqrt_tables.cpp
		Agg2D/src/Agg2D/agg_trans_affine.cpp
		Agg2D/src/Agg2D/agg_trans_double_path.cpp
		Agg2D/src/Agg2D/agg_trans_single_path.cpp
		Agg2D/src/Agg2D/agg_trans_warp_magnifier.cpp
		Agg2D/src/Agg2D/agg_vcgen_bspline.cpp
		Agg2D/src/Agg2D/agg_vcgen_contour.cpp
		Agg2D/src/Agg2D/agg_vcgen_dash.cpp
		Agg2D/src/Agg2D/agg_vcgen_markers_term.cpp
		Agg2D/src/Agg2D/agg_vcgen_smooth_poly1.cpp
		Agg2D/src/Agg2D/agg_vcgen_stroke.cpp
		Agg2D/src/Agg2D/agg_vpgen_clip_polygon.cpp
		Agg2D/src/Agg2D/agg_vpgen_clip_polyline.cpp
		Agg2D/src/Agg2D/agg_vpgen_segmentator.cpp
		Agg2D/src/Agg2D/ctrl/agg_bezier_ctrl.cpp
		Agg2D/src/Agg2D/ctrl/agg_cbox_ctrl.cpp
		Agg2D/src/Agg2D/ctrl/agg_gamma_ctrl.cpp
		Agg2D/src/Agg2D/ctrl/agg_gamma_spline.cpp
		Agg2D/src/Agg2D/ctrl/agg_polygon_ctrl.cpp
		Agg2D/src/Agg2D/ctrl/agg_rbox_ctrl.cpp
		Agg2D/src/Agg2D/ctrl/agg_scale_ctrl.cpp
		Agg2D/src/Agg2D/ctrl/agg_slider_ctrl.cpp
		Agg2D/src/Agg2D/ctrl/agg_spline_ctrl.cpp

		)

include_directories(
		#remove src/main/cpp/

		include/
		libyuv/include/
		libyuv/include/libyuv/
		Agg2D/inc/
		Agg2D/inc/Agg2D
)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
		simplecam

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})