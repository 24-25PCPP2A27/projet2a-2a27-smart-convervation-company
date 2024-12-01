#include "client.h"
#include <QDebug>
#include <QFile>

client::client()
{

}

bool client::Ajouterclient()
{
    QSqlQuery queryCheck;

    // Check if the dates exist in the produits table
    queryCheck.prepare("SELECT COUNT(*) FROM produits WHERE DATE_RECEPTION = :DATE_RECEPTION AND DATE_CONSERVATION = :DATE_CONSERVATION");
    queryCheck.bindValue(":DATE_RECEPTION", DATE_RECEPTION);
    queryCheck.bindValue(":DATE_CONSERVATION", DATE_CONSERVATION);
    if (!queryCheck.exec() || !queryCheck.next() || queryCheck.value(0).toInt() == 0) {
        qDebug() << "Dates do not exist in produits table. Inserting the dates.";
        QSqlQuery queryInsertProduits;
        queryInsertProduits.prepare("INSERT INTO produits (DATE_RECEPTION, DATE_CONSERVATION) VALUES (:DATE_RECEPTION, :DATE_CONSERVATION)");
        queryInsertProduits.bindValue(":DATE_RECEPTION", DATE_RECEPTION);
        queryInsertProduits.bindValue(":DATE_CONSERVATION", DATE_CONSERVATION);
        if (!queryInsertProduits.exec()) {
            qDebug() << "Error inserting dates into produits table:" << queryInsertProduits.lastError().text();
            return false;
        }
    }

    QSqlQuery query;

    query.prepare("INSERT INTO client (NOM, PRENOM, EMAIL, DATE_INSCRIPTION, AGE, SEXE, TELEPHONE, NB_SERVICE_RECU, DATE_RECEPTION, DATE_CONSERVATION) "
                  "VALUES (:NOM, :PRENOM, :EMAIL, :DATE_INSCRIPTION, :AGE, :SEXE, :TELEPHONE, :NB_SERVICE_RECU, :DATE_RECEPTION, :DATE_CONSERVATION)");

    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":EMAIL", EMAIL);
    query.bindValue(":DATE_INSCRIPTION", DATE_INSCRIPTION);
    query.bindValue(":AGE", AGE);
    query.bindValue(":SEXE", SEXE);
    query.bindValue(":TELEPHONE", TELEPHONE);
    query.bindValue(":NB_SERVICE_RECU", NB_SERVICE_RECU);
    query.bindValue(":DATE_RECEPTION", DATE_RECEPTION);
    query.bindValue(":DATE_CONSERVATION", DATE_CONSERVATION);

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return false;
    }

    // Add history
    historique histo;
    histo.setDATE_ACTION(QDateTime::currentDateTime());
    histo.setTYPE_ACTION("Ajout");
    histo.setDETAILS("Un client est ajouté: " + NOM + " " + PRENOM);
    histo.Ajouterhistorique();

    // Save history to file
    QFile file("C:/Users/chaim_if4qa5x/OneDrive/Bureau/Atelier_Connexion 2/history.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Impossible d'ouvrir le fichier!";
        return false;
    }

    QTextStream out(&file);
    out << "Date: " << histo.getDATE_ACTION().toString() << ", Type: " << histo.getTYPE_ACTION() << ", Details: " << histo.getDETAILS() << "\n";

    file.close();
    qDebug() << "Historique est enregistré avec succès!";

    return true;
}

QSqlQueryModel *client::Afficherclients()
{
    QSqlQueryModel *modal = new QSqlQueryModel();

    modal->setQuery("SELECT ID_CL, NOM, PRENOM, EMAIL, DATE_INSCRIPTION, AGE, SEXE, TELEPHONE, NB_SERVICE_RECU, DATE_RECEPTION, DATE_CONSERVATION, 'Update' ,'Delete' AS Action FROM client");
    modal->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_CL"));
    modal->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    modal->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    modal->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAIL"));
    modal->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_INSCRIPTION"));
    modal->setHeaderData(5, Qt::Horizontal, QObject::tr("AGE"));
    modal->setHeaderData(6, Qt::Horizontal, QObject::tr("SEXE"));
    modal->setHeaderData(7, Qt::Horizontal, QObject::tr("TELEPHONE"));
    modal->setHeaderData(8, Qt::Horizontal, QObject::tr("NB_SERVICE_RECU"));
    modal->setHeaderData(9, Qt::Horizontal, QObject::tr("DATE_RECEPTION"));
    modal->setHeaderData(10, Qt::Horizontal, QObject::tr("DATE_CONSERVATION"));
    modal->setHeaderData(11, Qt::Horizontal, QObject::tr("Action"));
    modal->setHeaderData(12, Qt::Horizontal, QObject::tr("Action")); // Set header for the new column

    return modal;
}

bool client::Modifierclient()
{
    QSqlQuery query;
    if (!query.prepare("UPDATE client SET NOM = :NOM, PRENOM = :PRENOM, EMAIL = :EMAIL, DATE_INSCRIPTION = :DATE_INSCRIPTION, AGE = :AGE, SEXE = :SEXE, TELEPHONE = :TELEPHONE, NB_SERVICE_RECU = :NB_SERVICE_RECU WHERE ID_CL = :ID_CL")) {
        qDebug() << "Prepare failed:" << query.lastError();
        return false;
    }

    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":EMAIL", EMAIL);
    query.bindValue(":DATE_INSCRIPTION", DATE_INSCRIPTION);
    query.bindValue(":AGE", AGE);
    query.bindValue(":SEXE", SEXE);
    query.bindValue(":TELEPHONE", TELEPHONE);
    query.bindValue(":NB_SERVICE_RECU", NB_SERVICE_RECU);
    query.bindValue(":ID_CL", ID_CL);

    if (!query.exec()) {
        qDebug() << "Exec failed:" << query.lastError();
        return false;
    }

    // Add history
    historique histo;
    histo.setDATE_ACTION(QDateTime::currentDateTime());
    histo.setTYPE_ACTION("Modification");
    histo.setDETAILS("Un client a été modifie: " + NOM + " " + PRENOM);
    histo.Ajouterhistorique();

    // Save history to file
    QFile file("C:/Users/chaim_if4qa5x/OneDrive/Bureau/Atelier_Connexion 2/history.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Impossible d'ouvrir le fichier!";
        return false;
    }

    QTextStream out(&file);
    out << "Date: " << histo.getDATE_ACTION().toString() << ", Type: " << histo.getTYPE_ACTION() << ", Details: " << histo.getDETAILS() << "\n";

    file.close();
    qDebug() << "Historique est enregistré avec succes!";

    return true;
}


bool client::Supprimerclient(const QString &ID_CL)
{
    QSqlQuery query;

    query.prepare("DELETE FROM client WHERE ID_CL = :ID_CL");
    query.bindValue(":ID_CL", ID_CL);

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return false;
    }

    // Add history
    historique histo;
    histo.setDATE_ACTION(QDateTime::currentDateTime());
    histo.setTYPE_ACTION("Suppression");
    histo.setDETAILS("Supprimer client avec l'ID " + ID_CL);
    histo.Ajouterhistorique();

    // Save history to file
    QFile file("C:/Users/chaim_if4qa5x/OneDrive/Bureau/Atelier_Connexion 2/history.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        qDebug() << "impossible d'ouvrir le fichier!";
        return false;
    }

    QTextStream out(&file);
    out << "Date: " << histo.getDATE_ACTION().toString() << ", Type: " << histo.getTYPE_ACTION() << ", Details: " << histo.getDETAILS() << "\n";

    file.close();
    qDebug() << "Historique est enregistré avec succes!";

    return true;
}




QSqlQueryModel *client::Rechercherclient(const QString &text)
{
    QSqlQueryModel *modal = new QSqlQueryModel();

    QString queryStr = QString("SELECT ID_CL, NOM, PRENOM, EMAIL, DATE_INSCRIPTION, AGE, SEXE, TELEPHONE, NB_SERVICE_RECU, DATE_RECEPTION, DATE_CONSERVATION,  'Update' AS Action, 'Delete' AS Action "
                               "FROM client WHERE ID_CL LIKE '%%1%' OR NOM LIKE '%%1%' OR PRENOM LIKE '%%1%' OR EMAIL LIKE '%%1%' OR DATE_INSCRIPTION LIKE '%%1%' OR AGE LIKE '%%1%' OR SEXE LIKE '%%1%' OR TELEPHONE LIKE '%%1%' OR NB_SERVICE_RECU LIKE '%%1%' OR DATE_RECEPTION LIKE '%%1%' OR DATE_CONSERVATION LIKE '%%1%'")
                           .arg(text);

    modal->setQuery(queryStr);
    modal->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_CL"));
    modal->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    modal->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    modal->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAIL"));
    modal->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_INSCRIPTION"));
    modal->setHeaderData(5, Qt::Horizontal, QObject::tr("AGE"));
    modal->setHeaderData(6, Qt::Horizontal, QObject::tr("SEXE"));
    modal->setHeaderData(7, Qt::Horizontal, QObject::tr("TELEPHONE"));
    modal->setHeaderData(8, Qt::Horizontal, QObject::tr("NB_SERVICE_RECU"));
    modal->setHeaderData(9, Qt::Horizontal, QObject::tr("DATE_RECEPTION"));
    modal->setHeaderData(10, Qt::Horizontal, QObject::tr("DATE_CONSERVATION"));
    modal->setHeaderData(11, Qt::Horizontal, QObject::tr("Action"));
    modal->setHeaderData(12, Qt::Horizontal, QObject::tr("Action"));

    return modal;
}

historique::historique()
{

}
bool historique::Ajouterhistorique()
{
    QSqlQuery query;

    query.prepare("INSERT INTO HISTORIQUE (DATE_ACTION,TYPE_ACTION,DETAILS) "
                  "VALUES ( :DATE_ACTION ,:TYPE_ACTION ,:DETAILS )");

    //query.bindValue(":ID_ACTION", this->ID_ACTION);
    query.bindValue(":DATE_ACTION", this->DATE_ACTION);
    query.bindValue(":TYPE_ACTION", this->TYPE_ACTION);
    query.bindValue(":DETAILS", this->DETAILS);


    return query.exec();
}

QSqlQueryModel *historique::Afficherhistorique()
{
    QSqlQueryModel *modal = new QSqlQueryModel();

    modal->setQuery("SELECT * FROM HISTORIQUE");
    modal->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_ACTION"));
    modal->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE_ACTION"));
    modal->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE_ACTION"));
    modal->setHeaderData(3, Qt::Horizontal, QObject::tr("DETAILS"));



    return modal;
}
