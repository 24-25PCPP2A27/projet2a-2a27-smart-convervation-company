#include "employe.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QRegExp>

#include <QPdfWriter>
#include <QPainter>

#include <QUuid>
Employe::Employe(int id, QString nom, QString prenom, QString email, QString mot_de_passe, QString date_dembau, int sal, int telephone) {
    this->idEm = id;
    this->nom = nom;
    this->prenom = prenom;
    this->email = email;
    this->mot_de_passe = mot_de_passe;
    this->date_dembau = date_dembau;
    this->sal = sal;
    this->telephone = telephone;
}

Employe::Employe() {}

QString Employe::getLastError() const {
    return lastErrorMessage;
}

void Employe::setLastError(const QString &error) {
    lastErrorMessage = error;
}

bool Employe::ajouter() {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open:" << db.lastError().text();
        setLastError("Database is not open.");
        return false;
    }

    if (!db.isValid()) {
        setLastError("Database connection is invalid.");
        return false;
    }


    if (!QRegExp("\\d{4}-\\d{2}-\\d{2}").exactMatch(date_dembau)) {
        qDebug() << "Invalid date format for DATE_D_EMBAUCHE:" << date_dembau;
        setLastError("Invalid date format. Expected format: YYYY-MM-DD.");
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYE (IDEM, NOM, PRENOM, EMAIL, MOT_DE_PASSE, DATE_D_EMBAUCHE, SALAIRE, TELEPHONE, RFID) "
                  "VALUES (:idEm, :nom, :prenom, :email, :mot_de_passe, :date_dembau, :sal, :telephone, :rfid)");
    query.bindValue(":rfid", rfid);
    query.bindValue(":idEm", idEm);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":mot_de_passe", mot_de_passe);
    query.bindValue(":date_dembau", date_dembau);
    query.bindValue(":sal", sal);
    query.bindValue(":telephone", telephone);
    query.bindValue(":rfid", rfid);
    qDebug() << "Executing query:" << query.executedQuery();
    qDebug() << "idEm:" << idEm << ", nom:" << nom << ", prenom:" << prenom
             << ", email:" << email << ", mot_de_passe:" << mot_de_passe
             << ", date_dembau:" << date_dembau << ", sal:" << sal
             << ", telephone:" << telephone
               << ", rfid:" << rfid ;

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        setLastError(query.lastError().text());
        return false;
    }

    qDebug() << "Query executed successfully.";
    return true;
}

bool Employe::modifier() {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur de Connexion"),
                              QObject::tr("La connexion à la base de données est fermée."), QMessageBox::Cancel);
        setLastError("Database is closed.");
        return false;
    }

    QSqlQuery query;
    query.prepare("UPDATE EMPLOYE SET NOM = :nom, PRENOM = :prenom, EMAIL = :email, MOT_DE_PASSE = :mot_de_passe, "
                  "DATE_D_EMBAUCHE = :date_dembau, SALAIRE = :sal, TELEPHONE = :telephone , RFID = : RFID"
                  "WHERE IDEM = :idEm");
    query.bindValue(":idEm", idEm);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":mot_de_passe", mot_de_passe);
    query.bindValue(":date_dembau", date_dembau);
    query.bindValue(":sal", sal);
    query.bindValue(":telephone", telephone);
    query.bindValue(": RFID", rfid);
    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        setLastError(query.lastError().text());
        QMessageBox::critical(nullptr, QObject::tr("Erreur d'Exécution"),
                              QObject::tr("Erreur lors de l'exécution de la requête.\n") + query.lastError().text(),
                              QMessageBox::Cancel);
        return false;
    }

    QMessageBox::information(nullptr, QObject::tr("Succès"),
                             QObject::tr("Données modifiées avec succès."), QMessageBox::Ok);
    return true;
}

bool Employe::supprimer(int idEm) {
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYE WHERE IDEM = :idEm");
    query.bindValue(":idEm", idEm);

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        setLastError(query.lastError().text());
        return false;
    }

    return true;
}

QSqlQueryModel* Employe::afficher() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IdEm"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Mot de passe"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date d'embauche"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Salaire"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("rfid"));
    return model;
}

QSqlQueryModel* Employe::rechercherParNomEtPrenom(const QString &nom, const QString &prenom) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("SELECT * FROM EMPLOYE WHERE NOM LIKE :nom AND PRENOM LIKE :prenom");
    query.bindValue(":nom", "%" + nom + "%");
    query.bindValue(":prenom", "%" + prenom + "%");

    if (query.exec()) {
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("IdEm"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Mot de passe"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date d'embauche"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("Salaire"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("Téléphone"));
        model->setHeaderData(8, Qt::Horizontal, QObject::tr("rfid"));
    } else {
        qDebug() << "Error executing query:" << query.lastError().text();
        setLastError(query.lastError().text());
    }

    return model;
}

QSqlQueryModel* Employe::trierParSalaire()
{
    QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery("SELECT * FROM EMPLOYE ORDER BY SALAIRE ASC");

        if (model->lastError().isValid()) {
            qDebug() << "Erreur lors de la requête de tri :" << model->lastError().text();
            return nullptr;
        }

        qDebug() << "Requête exécutée : " << model->query().executedQuery();
        qDebug() << "Nombre de lignes récupérées : " << model->rowCount();

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("IdEm"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Mot de passe"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date d'embauche"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("Salaire"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("Téléphone"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("rfid"));

        return model;
}


QMap<QString, double> Employe::getSalaryStatistics()
{
    QMap<QString, double> stats;
    QSqlQuery query;


    query.exec("SELECT SUM(SALAIRE) FROM EMPLOYE");
    if (query.next()) {
        stats["total"] = query.value(0).toDouble();
    }


    query.exec("SELECT AVG(SALAIRE) FROM EMPLOYE");
    if (query.next()) {
        stats["average"] = query.value(0).toDouble();
    }

    query.exec("SELECT MIN(SALAIRE) FROM EMPLOYE");
    if (query.next()) {
        stats["min"] = query.value(0).toDouble();
    }

    query.exec("SELECT MAX(SALAIRE) FROM EMPLOYE");
    if (query.next()) {
        stats["max"] = query.value(0).toDouble();
    }

    return stats;
}



bool Employe::checkEmailExists(const QString& email) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM employes WHERE email = :email");
    query.bindValue(":email", email);
    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    } else {
        qDebug() << "Error checking email:" << query.lastError().text();
        return false;
    }
}

bool Employe::resetPassword(const QString& email) {
    if (!checkEmailExists(email)) {
        return false;
    }

    QString newPassword = QUuid::createUuid().toString().mid(1, 8); // Generate an 8-character password
    QSqlQuery query;
    query.prepare("UPDATE employes SET password = :password WHERE email = :email");
    query.bindValue(":password", newPassword);
    query.bindValue(":email", email);

    if (query.exec()) {
        // Send email with the new password (mocked here)
        qDebug() << "New password for" << email << ":" << newPassword;
        return true;
    } else {
        qDebug() << "Error resetting password:" << query.lastError().text();
        return false;
    }
}
