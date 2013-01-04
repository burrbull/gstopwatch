#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <glib.h>

gboolean running;
GtkWidget *hbox;
GtkWidget *timer_display;
GtkWidget *window;
GTimer *timer;

void update_progress_bar () {
  gulong gulong;
  gdouble time_elapsed = g_timer_elapsed (timer, &gulong);
  char *output;

  sprintf(output, "%.2f", time_elapsed);

  gtk_label_set_text(GTK_LABEL(timer_display), output);
}

gboolean keypress (GtkWidget *widget, GdkEventKey *event) {

  guint(g) = event->keyval;

  if((g == GDK_KEY_space)) {
    if(running == FALSE) {
      g_timer_start(timer);
      running = TRUE;
      return TRUE;
    }
    else {
      g_timer_stop(timer);
      running = FALSE;
      return TRUE;
    }
  }
  return FALSE; 
}

int main (int argc, char *argv[]) {

  gtk_init (&argc, &argv);

  timer_display = gtk_label_new("");

  hbox = gtk_hbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX (hbox), timer_display, FALSE, FALSE, 5);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

  gtk_container_add (GTK_CONTAINER (window), hbox);
  gtk_widget_show_all (window);

  timer = g_timer_new ();
  g_timer_stop(timer);

  gint func_ref = g_timeout_add (50, update_progress_bar, NULL);
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(G_OBJECT(window), "key-press-event", G_CALLBACK(keypress), window);

  gtk_main ();
}
