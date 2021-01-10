#include <gtk/gtk.h>

///Structure possédant les données du contact
///Struct of the contact infos
typedef struct ContactType {
    gchar *Nom;
    gchar *Prenom;
    gchar *Adresse;
    gchar *Type_Contact;
    gchar *email;
    gchar *Numero;
}Contact;

///Les datas à passer au fonctions de callback
///Callback fonctions data struct
typedef struct minedata {
    GtkTreeIter iter;
    GtkTreeIter comboIter;
    GtkWidget *combo;
    GtkWidget *listStore;
    GtkWidget *window;
    GtkBuilder *build;
    gint nbr_Contact;
} mydata;

///Fonction callback afin de fermer la fenetre
///Callback fonc to close the main window
gboolean on_close (GtkWidget*, gpointer);
///Fonction callback pour delete un contact choisie et décrémenter le nombre de contact stocker
///Callback fonc to delete a choosen contact and decrease contact count
void Delete_Contact(GtkWidget*, gpointer);
///Fonction callback permettant d'éditer le contact choisie dans la combobox
///Callback fonc to edit a choosen contact in the combobox
void Edit_Contact(GtkWidget*, gpointer);
///Display le contact dans une boite de dialogue
///Display a contact in a dialog box
void Show_Contact(GtkButton*, gpointer);
///Add un contact avec ses information à la comboBox
///Add a contact with his informations in the combobox
void Add_Contact(GtkButton*, gpointer);