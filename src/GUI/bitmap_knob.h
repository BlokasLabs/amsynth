
#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

GtkWidget *bitmap_knob_new( GtkAdjustment *,
							GdkPixbuf *,
							guint frame_width,
							guint frame_height,
							guint frame_count );

void bitmap_knob_set_bg (GtkWidget *, GdkPixbuf *);

void bitmap_knob_set_parameter_index (GtkWidget *, unsigned long);

G_END_DECLS

