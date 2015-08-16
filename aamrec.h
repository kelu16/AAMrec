#ifndef AAMREC_H
#define AAMREC_H

#include <QMainWindow>
#include <QFileDialog>
#include <opencv2/opencv.hpp>
#include "../AAMlib/cvimagewidget.h"
#include "../AAMlib/trainingdata.h"
#include "../AAMlib/icaam.h"
#include "../AAMlib/robustaam.h"
#include "../AAMlib/sicaam.h"
#include "../AAMlib/fastsicaam.h"
#include "../AAMlib/wsicaam.h"
#include "../AAMlib/fourieraam.h"


using namespace std;
using namespace cv;

namespace Ui {
class AAMrec;
}

class AAMrec : public QMainWindow
{
    Q_OBJECT

public:
    explicit AAMrec(QWidget *parent = 0);
    ~AAMrec();

private slots:
    void loadImage();
    void loadTrainingData();
    void saveData();

    void buildAAM();

    void resetShape();
    void fittingStep();
    void fitImage();

    void changeUsedAAM();

private:
    Ui::AAMrec *ui;

    AAM* usedAAM;
    ICAAM icaam;
    RobustAAM raam;
    SICAAM sicaam;
    FastSICAAM fsicaam;
    WSICAAM wsicaam;
    FourierAAM faam;

    Mat fittingImage;
    string imageName;

    Mat groups;
    vector <string> descriptions;

    vector<TrainingData> trainingData;

    void loadTrainingData(string fileName);
    void loadImage(string fileName);
    void saveData(string fileName);

    void setUsedAAM(AAM* aam);

    void showFittingProgress();
    Mat drawShape(Mat image, Mat points);
};

#endif // AAMREC_H
