#include "mafenetre.h"

MaFenetre::MaFenetre(QWidget *parent) : QMainWindow (parent) {

    setFixedSize(800,600);

    read_csv(m_mat, m_vet, "../fichiers_ECBD_etudiants/data.csv");

    CMatString mes_maladies;

    for (unsigned i (0); i < m_mat[0].size(); ++i) {
        CVString mon_symptome;
        mes_maladies.push_back(mon_symptome);
        for (unsigned j (0); j < m_mat.size(); ++j) {
            mon_symptome.push_back(m_mat [j][i]);
        }
    }

    m_bou = new QPushButton("Quitter", this);
    m_bou->setGeometry(700,550,80,40);

    for (string symptome : m_vet) {
        m_symptomes.push_back(new QLabel (QString::fromStdString(symptome), this));
    }

    for (unsigned i (0); i < m_symptomes.size() - 1; ++i) {
        m_symptomes[i]->setFont(QFont("Arial", 12, QFont::Bold, true));
        m_symptomes[i]->move(200 + (int)i * 150, 125);
    }

    for (unsigned i (0); i < m_mat[0].size() - 1; ++i) {
        m_options.push_back(new QComboBox(this));
        m_options[i]->setGeometry(175 + (int)i * 150, 150, 100, 30);
        m_options[i]->addItem("NULL");
    }


    unsigned cpt (0);
    for (QComboBox *combo : m_options) {
        for (unsigned i (0); i < mes_maladies[0].size(); ++i) {
            if (notIn(mes_maladies[i], mes_maladies[i][cpt]))
                combo->addItem(QString::fromStdString(m_mat[i][cpt]));
        }
        ++cpt;
    }

    m_tra = new QLabel(this);
    m_tra->setFont(QFont("Arial", 12, QFont::Bold, true));
    m_tra->move(320, 300);


    connect(m_bou, SIGNAL(clicked()), this, SLOT(setQuitter()));
    //connect(m_com, SIGNAL(currentIndexChanged(const QString &)),this, SLOT(setCouleur()));
}

void MaFenetre::setQuitter () {
    exit(0);
}

bool MaFenetre::notIn(CVString tabStr, string strToTest) {
    for (string str : tabStr)
        return str == strToTest;
}

//void MaFenetre::setCouleur() {
//    this->couleur = m_com->currentText();
//    m_tra->setText(">> " + this->couleur + " <<");
//}
