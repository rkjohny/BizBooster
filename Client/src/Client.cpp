/**
 * @file    TradeXClient.cpp
 *
 * @brief   Implements the Client class.
 */

#include "Client.h"
#include "CilentConfig.h"
#include "ClientInitializer.h"
#include "AppFactory.h"

using namespace Common;
using namespace Client;

TradeXClient::TradeXClient(const WEnvironment& env)
: WApplication(env)
{

    ClientInitializer::Initialize();

    auto logger = AppFactory::GetLogger();

    LOG_DEBUG("Inside TradeXClient, writing to log file a debug message");
    logger->Debug(FL, LN, "Starting TradexClient  application");

    try {
        auto propertyReader = AppFactory::GetConfigReader(LANG_PROP_FILE_NAME);
        string apptitle = propertyReader->GetValueOf(LANG_PROP_KEY_APP_TITLE) + " - v" + CLIENT_VERSION;
        setTitle(WString(std::move(apptitle)));
    } catch (AppException &e) {
        LOG_ERROR(std::move(e.GetMessage()));
    }

    root()->addWidget(new WText("Your name, please ? ")); // show some text
    nameEdit_ = new WLineEdit(root()); // allow text input
    nameEdit_->setFocus(); // give focus

    WPushButton* button
            = new WPushButton("Greet me.", root()); // create a button
    button->setMargin(5, Left); // add 5 pixels margin

    root()->addWidget(new WBreak()); // insert a line break

    greeting_ = new WText(root()); // empty text

    /*
     * Connect signals with slots
     *
     * - simple Wt-way
     */
    button->clicked().connect(this, &TradeXClient::greet);

    /*
     * - using an arbitrary function object (binding values with boost::bind())
     */
    nameEdit_->enterPressed().connect
            (boost::bind(&TradeXClient::greet, this));

    /*
     * - using a c++0x lambda:
     */
    // button->clicked().connect(std::bind([=]() {
    //       greeting_->setText("Hello there, " + nameEdit_->text());
    // }));

    LOG_DEBUG("TradexClient  application started.");
}

void TradeXClient::greet()
{
    /*
     * Update the text, using text input into the nameEdit_ field.
     */
    greeting_->setText("Hello there, " + nameEdit_->text());
}

WApplication* CreateApplication(const WEnvironment& env)
{
    /*
     * You could read information from the environment to decide whether
     * the user has permission to start a new application
     */
    return new TradeXClient(env);
}

int main(int argc, char** argv)
{
    /*
     * Your main method may set up some shared resources, but should then
     * start the server application (FastCGI or httpd) that starts listening
     * for requests, and handles all of the application life cycles.
     *
     * The last argument to WRun specifies the function that will instantiate
     * new application objects. That function is executed when a new user surfs
     * to the Wt application, and after the library has negotiated browser
     * support. The function should return a newly instantiated application
     * object.
     */


    return WRun(argc, argv, &CreateApplication);
}
