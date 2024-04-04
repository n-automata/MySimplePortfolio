// Ryan Tu
// Networking - Lab 08 First Webpage
// Winter 2024
// main.cpp file

#define CROW_MAIN

#include "crow_all.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    crow::SimpleApp app;

    // default route - loads index.html
    CROW_ROUTE(app, "/")
    ([](const crow::request &req, crow::response &res)
     {
        ifstream in("../public/index.html", ifstream::in);
        if (in)
        {
            ostringstream contents;
            contents << in.rdbuf();
            in.close();
            res.write(contents.str());
        }
        else
        {
            res.write("Not Found");
        }
        res.end(); });

    // route for serving images
    CROW_ROUTE(app, "/images/<path>")
    ([](const crow::request &req, crow::response &res, const string &path)
     {
    ifstream file("../public/images/" + path);
    if (file.is_open()) 
    {
        ostringstream contents;
        contents << file.rdbuf();  
        file.close();  
        res.write(contents.str());
    }
    else
    {
        res.code = 404;  // set response code to 404
        res.write("Not Found");
    }
    res.end(); });

    // route for serving styles
    CROW_ROUTE(app, "/styles/<path>")
    ([](const crow::request &req, crow::response &res, const string &path)
     {
    ifstream file("../public/styles/" + path);
    if (file.is_open()) {
        ostringstream contents;
        contents << file.rdbuf();  
        file.close();  
        res.write(contents.str());
    }
    else
    {
        res.code = 404;  
        res.write("Not Found");
    }
    res.end(); });

    // route for serving scripts
    CROW_ROUTE(app, "/scripts/<path>")
    ([](const crow::request &req, crow::response &res, const string &path)
     {
    ifstream file("../public/scripts/" + path);
    if (file.is_open()) {
        ostringstream contents;
        contents << file.rdbuf();  
        file.close();  
        res.write(contents.str());
    }
    else
    {
        res.code = 404;  
        res.write("Not Found");
    }
    res.end(); });

    // route for serving Profile.html
    CROW_ROUTE(app, "/Profile.html")
    ([](const crow::request &req, crow::response &res)
     {
        ifstream in("../public/Profile.html", ifstream::in);
        if (in)
        {
            ostringstream contents;
            contents << in.rdbuf();
            in.close();
            res.write(contents.str());
        }
        else
        {
            res.code = 404;
            res.write("Not Found");
        }
        res.end(); });

    // handles generic route for HTML pages - (ex. going back to index.html from the profile page)
    CROW_ROUTE(app, "/<string>")
    ([](const crow::request &req, crow::response &res, const string &path)
     {
        ifstream file("../public/" + path);
        if (file.is_open()) 
        {
            ostringstream contents;
            contents << file.rdbuf();
            file.close();
            res.write(contents.str());
        } else 
        {
            res.code = 404;
            res.write("Not Found");
        }
        res.end(); });

    app.port(8080).multithreaded().run(); // use port 8080

    return 1;
}
