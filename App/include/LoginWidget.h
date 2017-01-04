/**
 * Author: Rezaul Karim
 * Email: rkjohny@gmail.com
 *
 * Copyright (C) 20016 Rezaul Karim (rkjohny@gmail.com) all rights reserved.
 *
 * The information contained here-in is the property of Rezaul Karim and is not to be
 * disclosed or used without prior written permission of Rezaul Karim. This copyright
 * extends to all media in which this information may be preserved including
 * magnetic storage, computer print-out or visual display.
 */


#ifndef LOGIN_WIDGET_H
#define LOGIN_WIDGET_H


#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>

namespace WebApp {

class LoginWidget : public Wt::WContainerWidget {
public:
    LoginWidget(Wt::WContainerWidget *parent);
    virtual ~LoginWidget();
    
    void Login();
    
private:
    Wt::WText *m_txtUserName;
    Wt::WLineEdit *m_userName;
    Wt::WLineEdit *m_password;
    Wt::WPushButton *m_login;
};

}
#endif /* LOGIN_WIDGET_H */

