#include    <gbox.h>

struct _GBox {
    GtkWidget* parent;
};

G_DEFINE_TYPE (GBox, gbox, GBOX_TYPE)

static void gbox_init(GBox* box) {
    g_print("GBox Initialize\n");
}

static void gbox_class_init(GBoxClass* class) {
    g_print("GBox Class Initialize\n");
}

GBox* gbox_new(GtkOrientation orientation, int spacing) {
    return g_object_new(GBOX_TYPE, "orientation", orientation, "spacing", spacing, NULL);
}