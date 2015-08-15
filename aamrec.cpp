#include "aamrec.h"
#include "ui_aamrec.h"

AAMrec::AAMrec(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AAMrec)
{
    ui->setupUi(this);

    connect(ui->actionLoad_Training_Data, SIGNAL(triggered()), SLOT(loadTrainingData()));
    connect(ui->actionLoad_Image, SIGNAL(triggered()), SLOT(loadImage()));
    connect(ui->actionSave_Data, SIGNAL(triggered()), SLOT(saveData()));

    connect(ui->actionBuild_AAM, SIGNAL(triggered()), SLOT(buildAAM()));

    connect(ui->actionFit_Image, SIGNAL(triggered()), SLOT(fitImage()));
    connect(ui->actionExecute_fitting_step, SIGNAL(triggered()), SLOT(fittingStep()));
    connect(ui->actionReset_Shape, SIGNAL(triggered()), SLOT(resetShape()));

    connect(ui->actionIC_AAM, SIGNAL(triggered()), SLOT(changeUsedAAM()));
    connect(ui->actionSIC_AAM, SIGNAL(triggered()), SLOT(changeUsedAAM()));
    connect(ui->actionRobust_AAM, SIGNAL(triggered()), SLOT(changeUsedAAM()));
    connect(ui->actionWSIC_AAM, SIGNAL(triggered()), SLOT(changeUsedAAM()));

    string filePath = "/home/lucas/Dropbox/Diplomarbeit/Code/trainingdata/";

    loadTrainingData(filePath+"data1.xml");
    loadTrainingData(filePath+"data2.xml");
    loadTrainingData(filePath+"data3.xml");
    loadTrainingData(filePath+"data4.xml");
    loadTrainingData(filePath+"data5.xml");
    loadTrainingData(filePath+"data6.xml");
    loadTrainingData(filePath+"data7.xml");
    loadTrainingData(filePath+"data8.xml");
    loadTrainingData(filePath+"data9.xml");
    loadTrainingData(filePath+"data10.xml");
    loadTrainingData(filePath+"data11.xml");
    loadTrainingData(filePath+"data12.xml");
    loadTrainingData(filePath+"data13.xml");
    loadTrainingData(filePath+"data14.xml");
    loadTrainingData(filePath+"data15.xml");
    loadTrainingData(filePath+"data16.xml");
    loadTrainingData(filePath+"data17.xml");

    //loadTrainingData(filePath+"Rafd090_01_Caucasian_female_angry_frontal.xml");
    //loadTrainingData(filePath+"Rafd090_01_Caucasian_female_contemptuous_frontal.xml");
    //loadTrainingData(filePath+"Rafd090_01_Caucasian_female_disgusted_frontal.xml");
    //loadTrainingData(filePath+"Rafd090_01_Caucasian_female_fearful_frontal.xml");
    //loadTrainingData(filePath+"Rafd090_01_Caucasian_female_happy_frontal.xml");
    //loadTrainingData(filePath+"Rafd090_01_Caucasian_female_neutral_frontal.xml");
    //loadTrainingData(filePath+"Rafd090_01_Caucasian_female_sad_frontal.xml");
    //loadTrainingData(filePath+"Rafd090_01_Caucasian_female_surprised_frontal.xml");

    loadTrainingData(filePath+"Rafd090_03_Caucasian_male_angry_frontal.xml");
    loadTrainingData(filePath+"Rafd090_03_Caucasian_male_contemptuous_frontal.xml");
    loadTrainingData(filePath+"Rafd090_03_Caucasian_male_disgusted_frontal.xml");
    loadTrainingData(filePath+"Rafd090_03_Caucasian_male_fearful_frontal.xml");
    loadTrainingData(filePath+"Rafd090_03_Caucasian_male_happy_frontal.xml");
    loadTrainingData(filePath+"Rafd090_03_Caucasian_male_neutral_frontal.xml");
    loadTrainingData(filePath+"Rafd090_03_Caucasian_male_sad_frontal.xml");
    loadTrainingData(filePath+"Rafd090_03_Caucasian_male_surprised_frontal.xml");

    loadTrainingData(filePath+"Rafd090_07_Caucasian_male_angry_frontal.xml");
    loadTrainingData(filePath+"Rafd090_07_Caucasian_male_contemptuous_frontal.xml");
    loadTrainingData(filePath+"Rafd090_07_Caucasian_male_disgusted_frontal.xml");
    loadTrainingData(filePath+"Rafd090_07_Caucasian_male_fearful_frontal.xml");
    loadTrainingData(filePath+"Rafd090_07_Caucasian_male_happy_frontal.xml");
    loadTrainingData(filePath+"Rafd090_07_Caucasian_male_neutral_frontal.xml");
    loadTrainingData(filePath+"Rafd090_07_Caucasian_male_sad_frontal.xml");
    loadTrainingData(filePath+"Rafd090_07_Caucasian_male_surprised_frontal.xml");

    this->setUsedAAM(&icaam);
    this->ui->actionIC_AAM->setChecked(true);
    this->buildAAM();
}

AAMrec::~AAMrec()
{
    delete ui;
}

void AAMrec::loadTrainingData() {
    QStringList fileNames = QFileDialog::getOpenFileNames(this, "Open file", "", "*.xml");
    if(!fileNames.isEmpty()) {
        for(int i=0; i<fileNames.size(); i++) {
            loadTrainingData(fileNames.at(i).toLocal8Bit().data());
        }
    }
}

void AAMrec::loadTrainingData(string fileName) {
    TrainingData td;
    td.loadDataFromFile(fileName);
    this->groups = td.getGroups();
    this->descriptions = td.getDescriptions();
    this->trainingData.push_back(td);
}

void AAMrec::loadImage() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open file", "", tr("Image Files (*.png *.jpg *.gif)"));
    if(!fileName.isEmpty()) {
        loadImage(fileName.toLocal8Bit().data());
    }
}

void AAMrec::loadImage(string fileName) {
    this->fittingImage = imread(fileName);

    this->imageName = fileName.substr(fileName.find_last_of("/\\") + 1);
    this->setWindowTitle(QString::fromStdString(this->imageName));

    ui->outImage->showImage(this->fittingImage);

    usedAAM->setFittingImage(this->fittingImage);

    if(usedAAM->isInitialized()) {
        usedAAM->resetShape();
    }
}

void AAMrec::saveData() {
    string file = this->imageName.substr(0,this->imageName.find_last_of('.'))+".xml";
    QString fileName = QFileDialog::getSaveFileName(this, "Save file", QString::fromStdString(file), "*.xml");

    saveData(fileName.toLocal8Bit().data());
}

void AAMrec::saveData(string fileName) {
    TrainingData td;
    td.setPoints(usedAAM->getFittingShape());
    td.setImage(this->fittingImage);
    td.setDescriptions(this->descriptions);
    td.setGroups(this->groups);
    td.saveDataToFile(fileName);
}

void AAMrec::changeUsedAAM() {
    QObject *s = sender();
    ui->actionIC_AAM->setChecked(false);
    ui->actionSIC_AAM->setChecked(false);
    ui->actionRobust_AAM->setChecked(false);
    ui->actionWSIC_AAM->setChecked(false);

    if(s == ui->actionIC_AAM) {
        ui->actionIC_AAM->setChecked(true);
        this->setUsedAAM(&icaam);
    } else if(s == ui->actionSIC_AAM) {
        ui->actionSIC_AAM->setChecked(true);
        this->setUsedAAM(&sicaam);
    } else if(s == ui->actionRobust_AAM) {
        ui->actionRobust_AAM->setChecked(true);
        this->setUsedAAM(&raam);
    } else if(s == ui->actionWSIC_AAM) {
        ui->actionWSIC_AAM->setChecked(true);
        this->setUsedAAM(&wsicaam);
    }

    if(!this->fittingImage.empty()) {
        this->usedAAM->setFittingImage(this->fittingImage);
    }
}

void AAMrec::setUsedAAM(AAM *aam) {
    this->usedAAM = aam;
}

void AAMrec::buildAAM() {
    if(!this->trainingData.empty()) {
        for(unsigned int i=0; i<this->trainingData.size(); i++) {
            TrainingData td = trainingData.at(i);
            Mat p = td.getPoints();
            Mat img = td.getImage();

            usedAAM->addTrainingData(p, img);
        }

        usedAAM->train();
    }
}

void AAMrec::fitImage() {
    if(usedAAM->isInitialized() && usedAAM->hasFittingImage()) {
        usedAAM->resetShape();

        float fittingChange = 20.0f;
        float fitThreshold = 0.05f;
        int steps = 0;

        while(fittingChange > fitThreshold && steps<100) {
            fittingChange = usedAAM->fit();
            steps++;
        }

        cout<<"Steps: "<<steps<<endl;

        this->showFittingProgress();
    }
}

void AAMrec::fittingStep() {
    if(usedAAM->isInitialized() && usedAAM->hasFittingImage()) {
        high_resolution_clock::time_point start_fit = high_resolution_clock::now();
        cout<<usedAAM->fit()<<endl;
        high_resolution_clock::time_point end_fit = high_resolution_clock::now();
        cout<<"Time: "<<duration_cast<milliseconds>(end_fit - start_fit).count()<<endl;
        this->showFittingProgress();
    }
}

void AAMrec::resetShape() {
    if(usedAAM->isInitialized() && usedAAM->hasFittingImage()) {
        usedAAM->resetShape();
        this->showFittingProgress();
    }
}

Mat AAMrec::drawShape(Mat image, Mat points) {
    if(!usedAAM->triangles.empty()) {
        for(int i=0; i<usedAAM->triangles.rows; i++) {
            Point a,b,c;
            a = icaam.getPointFromMat(points, usedAAM->triangles.at<int>(i,0));
            b = icaam.getPointFromMat(points, usedAAM->triangles.at<int>(i,1));
            c = icaam.getPointFromMat(points, usedAAM->triangles.at<int>(i,2));

            line(image, a, b, Scalar(255,0,255),1);
            line(image, a, c, Scalar(255,0,255),1);
            line(image, b, c, Scalar(255,0,255),1);
        }
    }

    return image;
}

void AAMrec::showFittingProgress() {
    Mat image = fittingImage.clone();
    if(usedAAM->isInitialized()) {
        Mat p = usedAAM->getFittingShape();
        image = drawShape(image, p);
    }
    /*
    namedWindow("Fitting");
    imshow("Fitting", image);
    */
    ui->outImage->showImage(image);
}
