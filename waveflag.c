#include <cairo.h>

static void
outline_path (cairo_t *cr)
{
	cairo_move_to (cr, 127.15,81.52);
	cairo_rel_line_to (cr, -20.51,-66.94);
	cairo_rel_curve_to (cr, -0.61,-2,-2.22,-3.53,-4.25,-4.03);
	cairo_rel_curve_to (cr, -0.48,-0.12,-0.96,-0.18,-1.44,-0.18);
	cairo_rel_curve_to (cr, -1.56,0,-3.07,0.61,-4.2,1.74);
	cairo_rel_curve_to (cr, -9.56,9.56,-17.94,11.38,-30.07,11.38);
	cairo_rel_curve_to (cr, -3.68,0,-7.72,-0.18,-11.99,-0.38);
	cairo_rel_curve_to (cr, -3.37,-0.15,-6.85,-0.31,-10.62,-0.4);
	cairo_rel_curve_to (cr, -0.66,-0.02,-1.31,-0.02,-1.95,-0.02);
	cairo_rel_curve_to (cr, -30.67,0,-40.49,18.56,-40.89,19.35);
	cairo_rel_curve_to (cr, -0.52,1.01,-0.73,2.16,-0.62,3.29);
	cairo_rel_line_to (cr, 6.72,66.95);
	cairo_rel_curve_to (cr, 0.22,2.22,1.67,4.13,3.75,4.95);
	cairo_rel_curve_to (cr, 0.7,0.27,1.43,0.4,2.16,0.4);
	cairo_rel_curve_to (cr, 1.43,0,2.84,-0.52,3.95,-1.5);
	cairo_rel_curve_to (cr, 0.1,-0.09,12.42,-10.63,32.13,-10.63);
	cairo_rel_curve_to (cr, 2.52,0,5.09,0.17,7.64,0.51);
	cairo_rel_curve_to (cr, 9.27,1.23,16.03,1.78,21.95,1.78);
	cairo_rel_curve_to (cr, 18.93,0,32.93,-6.1,46.82,-20.38);
	cairo_curve_to (cr, 127.24,85.85,127.79,83.59,127.15,81.52);
	cairo_close_path (cr);
}

static cairo_pattern_t *
mesh_create (void)
{
	cairo_pattern_t *pattern = cairo_pattern_create_mesh();
	cairo_mesh_pattern_begin_patch(pattern);

	cairo_mesh_pattern_line_to(pattern,   -1,  43);
	cairo_mesh_pattern_curve_to(pattern,  32,  -4,
					      77,  48,
					     104,   0);
	cairo_mesh_pattern_line_to(pattern,  129,  85);
	cairo_mesh_pattern_curve_to(pattern,  78, 138,
					      53,  80,
					      8,  126);

	cairo_mesh_pattern_set_corner_color_rgb(pattern, 0, 0, 0, .5);
	cairo_mesh_pattern_set_corner_color_rgb(pattern, 1, 1, 0, .5);
	cairo_mesh_pattern_set_corner_color_rgb(pattern, 2, 1, 1, .5);
	cairo_mesh_pattern_set_corner_color_rgb(pattern, 3, 0, 1, .5);

	cairo_mesh_pattern_end_patch(pattern);
	return pattern;
}


#define SCALE 8.
#define SIZE 128
#define MARGIN_X 1
#define MARGIN_Y 1

int
main (int argc, char **argv)
{
	cairo_surface_t *surface;
	cairo_pattern_t *mesh;
	cairo_t *cr;
	
	surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32,
					      (SIZE+2*MARGIN_X)*SCALE,
					      (SIZE+2*MARGIN_Y)*SCALE);
	cr = cairo_create (surface);
	cairo_scale (cr, SCALE, SCALE);
	cairo_translate (cr, MARGIN_X, MARGIN_Y);

	mesh = mesh_create ();
	cairo_set_source (cr, mesh);
	cairo_pattern_destroy (mesh);

	cairo_paint (cr);
	outline_path (cr);
	cairo_set_source_rgba (cr, 1.,1.,1.,.5);
	cairo_stroke (cr);

	cairo_surface_write_to_png (surface, "out.png");

	return 0;
}
