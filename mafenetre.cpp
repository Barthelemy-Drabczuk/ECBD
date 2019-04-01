#include "mafenetre.h"

MaFenetre::MaFenetre(QWidget *parent) : QMainWindow (parent) {

    setFixedSize(800,600);

    read_csv(m_mat, m_vet, "../ECBD/fichiers_ECBD_etudiants/data.csv");

    m_bou = new QPushButton("Quitter", this);
    m_bou->setGeometry(700,550,80,40);

    for (string symptome : m_vet) {
        m_symptomes.push_back(new QLabel (QString::fromStdString(symptome), this));
    }

    for (unsigned i (0); i < m_symptomes.size() - 1; ++i) {
        m_symptomes[i]->setFont(QFont("Arial", 12, QFont::Bold, true));
        m_symptomes[i]->move(200 + int (i) * 150, 125);
    }

    for (unsigned i (0); i < m_mat[0].size() - 1; ++i) {
        m_options.push_back(new QComboBox(this));
        m_options[i]->setGeometry(175 + int (i) * 150, 150, 100, 30);
        m_options[i]->addItem("NULL");
    }


    unsigned cpt (0);
    for (QComboBox *combo : m_options) {
        for (unsigned i (0); i < m_mat.size (); ++i) {
            cout << m_mat[i][cpt] << endl;
            combo->addItem(QString::fromStdString(m_mat[i][cpt]));
        }
        ++cpt;
    }

    predir = new QPushButton("Predir", this);
    predir->setGeometry(175, 200, 100, 30);

    m_tra = new QLabel(this);
    m_tra->setFont(QFont("Arial", 12, QFont::Bold, true));


    connect(m_bou, SIGNAL(clicked()), this, SLOT(setQuitter()));
    connect(predir, SIGNAL(clicked ()), this, SLOT(setMaladie()));
}

QString MaFenetre::predirMaladie(vector<QString> symptomes) {
    vector <double> tabScore;

    vector<pair<string, double>> tabFreq;

    for (unsigned i (0); i < m_mat.size(); ++i) {
        cout << m_mat [i][m_mat[0].size() - 1] << endl;
        if (tabFreq.size() == 0)
            tabFreq.push_back(make_pair (m_mat[i][m_mat[0].size() - 1], 1.0/m_mat.size()));
        else {
            bool isIn = false;
            unsigned cpt (0);
            for (pair<string, double> &mon_score : tabFreq) {
                cout << mon_score.first << endl;
                if (mon_score.first == m_mat[i][m_mat[0].size() - 1]){
                    mon_score.second = mon_score.second + 1.0/double(m_mat.size());
                    isIn = true;
                }
                else {
                    if ( (!isIn) && (cpt == (tabFreq.size() - 1)) ) {
                        tabFreq.push_back(make_pair (m_mat[i][m_mat[0].size() - 1], 1.0/double(m_mat.size())));
                    }
                    else {
                        ++cpt;
                    }
                }
            }
        }
    }
    for (pair <string, double> mon_score : tabFreq) {
        cout << mon_score.first << " : " << mon_score.second << endl;
    }

    for (unsigned i (0); i < tabFreq.size() - 1; ++i) {
        tabScore.push_back(tabFreq [i].second);
    }

    unsigned cptNull = 0;
    for (QString qstr : symptomes) {
        if (qstr.toStdString() == "NULL") {
            ++cptNull;
        }
        else {
            unsigned cptNbMaladie (0);
            for (unsigned i (0); i < tabFreq.size() - 1; ++i) {
                unsigned cptApparitionSymptome (0);
                 for (unsigned j (0); j < m_mat.size() - 1; ++j) {
                     if (tabFreq[i].first == m_mat[j][m_mat[j].size() - 1]) {
                         ++cptNbMaladie;
                         cout << "maladie : " << tabFreq[i].first << endl;
                     }
                     for (unsigned k (0); k < m_mat[j].size() - 1; ++k) {
                         if ( (qstr.toStdString() == m_mat[j][k]) && (tabFreq[i].first == m_mat[j][m_mat[j].size() - 1]) ) {
                             ++cptApparitionSymptome;
                             cout << "cptApparitionSymptome : " << cptApparitionSymptome << endl;
                         }
                     }
                 }
                 cout << "score : " << double(cptApparitionSymptome)/((cptNbMaladie == 0) ? 1 : double(cptNbMaladie)) << endl;
                 tabFreq[i].second *= double(cptApparitionSymptome)/((cptNbMaladie == 0) ? 1 : double(cptNbMaladie));
                 cout << tabFreq[i].first << " : " << tabFreq[i].second << endl;
            }
        }
    }

    if (cptNull == symptomes.size()) {
        return QString("NULL");
    }
    else {
        string maladie;
        double max_score = 0.0;
        for (pair<string, double> mon_score : tabFreq) {
            if (mon_score.second > max_score) {
                max_score = mon_score.second;
                maladie = mon_score.first;
            }
            else if ( (mon_score.second <= max_score + 0.00001) && (mon_score.second >= max_score - 0.00001)) {
                maladie += ('/'+ mon_score.first);
            }
        }
        return QString::fromStdString(maladie);
    }
}

void MaFenetre::setQuitter () {
    exit(0);
}

void MaFenetre::setMaladie() {
    vector <QString> symptomes;
    for (QComboBox *combo : m_options) {
        symptomes.push_back(combo->currentText());
    }

    m_tra->setGeometry(320, 250, 300,30);
    m_tra->setText(predirMaladie(symptomes));
}

