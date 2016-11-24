/**
 * @file    TradeXClient.h
 *
 * @brief   Declares the TradeXClient class.
 *
 * Copyright (C) 2016 ABC Corporation.
 */

#ifndef TRADE_X_CLIENT_H
#define TRADE_X_CLIENT_H


#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>

using namespace Wt;


namespace Client
{

/**
 * @class   TradeXClient
 *
 * @brief   Main clqass of TradeXClient.
 *
 * @author  Rezaul
 * @date    8/23/2016
 */

class TradeXClient : public WApplication
{
public:
    /**
     * @fn  TradeXClient::TradeXClient(const WEnvironment& env);
     *
     * @brief   Constructor.
     *
     * @author  Rezaul
     * @date    8/23/2016
     *
     * @param   env contains information about the new session, and the initial request
     */
    TradeXClient( const WEnvironment& env );

private:
    WLineEdit* nameEdit_;
    WText* greeting_;

    void greet();
};


}
#endif
