#ifndef MYGUI_H
#define MYGUI_H
void createmyButton(Mat& img, const char* text, int x, int y, Scalar background, Scalar foreground){
    vector<Point> contour;
    contour.push_back(Point(x +10,y));
    contour.push_back(Point(x+130,y));
    contour.push_back(Point(x+120,y+30));
    contour.push_back(Point(x,y+20));
    const cv::Point *pts = (const cv::Point*) Mat(contour).data;
    int npts = Mat(contour).rows;
    // draw the polygon
    fillPoly(img, &pts,&npts, 1, background, 1);
    Size textSize = getTextSize(text, FONT_HERSHEY_COMPLEX_SMALL, 1, 1, 0);
    putText(img, text, cvPoint(contour[1].x/2+x/2-textSize.width/2, contour[0].y + 15),
    FONT_HERSHEY_COMPLEX_SMALL, 1, foreground, 1, CV_8UC3);
}
void createmyCounter(Mat& img, const int value, int x, int y, Scalar background, Scalar foreground){
    vector<Point> contour;
    contour.push_back(Point(x+10, y));
    contour.push_back(Point(x+60, y));
    contour.push_back(Point(x+50, y+30));
    contour.push_back(Point(x, y+20));
    const cv::Point *pts = (const cv::Point*) Mat(contour).data;
    int npts = Mat(contour).rows;
    // draw the polygon
    stringstream s;
    s << value;
    string st = s.str();
    fillPoly(img, &pts, &npts, 1, background, 1);
    Size textSize = getTextSize(st.c_str(), FONT_HERSHEY_COMPLEX_SMALL, 1, 1, 0);
    putText(img, st.c_str(), cvPoint(contour[1].x/2+x/2-textSize.width/2, contour[0].y + 15),
    FONT_HERSHEY_COMPLEX_SMALL, 1, foreground, 1, CV_8UC3);
    vector<Point> contour2;
    contour2.push_back(Point(x+70, y));
    contour2.push_back(Point(x+75, y+10));
    contour2.push_back(Point(x+65, y+10));
    pts = (const cv::Point*) Mat(contour2).data;
    npts = Mat(contour2).rows;
    fillPoly(img, &pts, &npts, 1, background, 1);
    for(int i=0;i<contour2.size();i++)
        contour2[i].y += 10;
    contour2[0].y +=20;
    fillPoly(img, &pts, &npts, 1, background, 1);
}
void createmyLabel(Mat& img, const char* text, int x, int y, Scalar textcolor){
    Size textSize = getTextSize(text, FONT_HERSHEY_COMPLEX_SMALL, 1, 1, 0);
    putText(img, text, cvPoint(x, y + 15),
    FONT_HERSHEY_COMPLEX_SMALL, 1, textcolor, 1, CV_8UC3);
}
#endif //MYGUI_H
