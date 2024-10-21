#include "employe.h"

employe::employe(int id, QString nom, QString prenom, QString email, QString mot_de_passe, QString date_dembau, int sal, int telephone)
{
    this->idEm = idEm;
    this->nom = nom;
    this->prenom = prenom;
    this->email = email;
    this->mot_de_passe = mot_de_passe;
    this->date_dembau = date_dembau;
    this->sal = sal;
    this->telephone = telephone;

}

bool employe::ajouter() {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid()) {
        QMessageBox::critical(nullptr, QObject::tr("ERREUR DE LA CONNEXION A LA BASE"),
                              QObject::tr("ERREUR DE LA CONNEXION A LA BASE.\nClick cancel to exit."),
                              QMessageBox::Cancel);
        return false;
    }

    QSqlQuery query(db);

    query.prepare("INSERT INTO EMPOLYE (CIN, NOM, PRENOM, DATENAISS, GENRE, EMAIL, DESCRIPTION, IMAGE_A) "
                  "VALUES (:cin, :nom, :prenom, :datenaiss, :genre, :email, :description, :image_a)");

    query.bindValue(":cin", cin);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":datenaiss", datenaiss);
    query.bindValue(":genre", genre);
    query.bindValue(":email", email);
    query.bindValue(":description", description);
    query.bindValue(":image_a", image_a);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, QObject::tr("ERREUR D'EXECUTION"),
                              QObject::tr("ERREUR D'EXECUTION DE LA REQUETE.\n"),
                              QMessageBox::Cancel);
        return false;
    } else {
        QMessageBox::information(nullptr, QObject::tr("SUCCES"),
                                 QObject::tr("DONNEES INSEREES AVEC SUCCES."),
                                 QMessageBox::Ok);
        return true;
    }
}

bool Employee::supprimer(int idEm) {
    QSqlQuery query;
    QString res = QString::number(idEm);
    query.prepare("DELETE FROM EMPLOYEES WHERE IDEM = :idEm");
    query.bindValue(":idEm", res);
    return query.exec();

}

QSqlQueryModel* Employee::afficher() {
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYEES");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IdEm"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Mot de passe"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date d'embauche"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Disponibilité"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Salaire"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Téléphone"));
    return model;
}
