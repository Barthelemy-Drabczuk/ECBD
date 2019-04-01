#ifndef MAFENETRE_H
#define MAFENETRE_H

#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QString>
#include "fichiers_ECBD_etudiants/charger_csv.h"

class MaFenetre : public QMainWindow {

    Q_OBJECT //OBLIGATOIRE

    public slots:
        void setQuitter ();
        //void setCouleur ();
        void setMaladie ();

    public :
        MaFenetre(QWidget *parent = 0);
        QString predirMaladie (vector<QString> symptomes);

    private :
        QLabel *m_tra;
        vector<QLabel *> m_symptomes;
        QPushButton *m_bou, *predir;
        vector<QComboBox *> m_options;
        QString couleur;
        CVString m_vet;
        CMatString m_mat;

        bool notIn (CVString tabStr, string strToTest);
};

#endif // MAFENETRE_H
