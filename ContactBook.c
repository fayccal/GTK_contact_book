#include "contactFonc.h"

int main(int argc,char *argv[]){

    mydata userdata;
    userdata.nbr_Contact=0;
    gtk_init(&argc,&argv);
    //Chargement du fichier glade
    //We load the glade file 
    userdata.build=gtk_builder_new_from_file("gladeContactBook.glade");
    userdata.window=(GtkWidget*) gtk_builder_get_object(userdata.build,"window");
    g_signal_connect(G_OBJECT(userdata.window),"delete_event",G_CALLBACK(on_close),&userdata);

    userdata.listStore=(GtkWidget*) gtk_builder_get_object(userdata.build,"liststore1");
    userdata.combo=(GtkWidget*) gtk_builder_get_object(userdata.build,"combo");
    
    GtkCellRenderer* rcell1 = gtk_cell_renderer_text_new ();
    GtkCellRenderer* rcell2 = gtk_cell_renderer_text_new ();
    GtkCellRenderer* rcell5 = gtk_cell_renderer_text_new ();
    //On dit à la combobox de ne montrer que le nom, prénom et numéro de téléphone
    //We say to the combobox to display in it only the firstname, lastname and the phone number
    gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(userdata.combo),rcell1,FALSE);
    gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(userdata.combo),rcell1,"text",0,NULL);

    gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(userdata.combo),rcell2,FALSE);
    gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(userdata.combo),rcell2,"text",1,NULL);

    gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(userdata.combo),rcell5,FALSE);
    gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(userdata.combo),rcell5,"text",5,NULL);
    //Connection des fonctions callback
    //Connection of the callback fonctions
    g_signal_connect(gtk_builder_get_object(userdata.build,"AddContact"),"clicked",G_CALLBACK(Add_Contact),&userdata);
    g_signal_connect(gtk_builder_get_object(userdata.build,"Display"),"clicked",G_CALLBACK(Show_Contact),&userdata);
    g_signal_connect(gtk_builder_get_object(userdata.build,"EditBtn"),"clicked",G_CALLBACK(Edit_Contact),&userdata);
    g_signal_connect(gtk_builder_get_object(userdata.build,"Delete"),"clicked",G_CALLBACK(Delete_Contact),&userdata);    
    gtk_widget_show_all(userdata.window);
    gtk_main();
    return 0;
}
