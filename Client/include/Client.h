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

#ifndef CLIENT_H
#define CLIENT_H


#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>

using namespace Wt;


namespace Client {

    /**
     * @class   TradeXClient
     *
     * @brief   Main clqass of TradeXClient.
     *
     * @author  Rezaul
     * @date    8/23/2016
     */

    class TradeXClient : public WApplication {
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
        TradeXClient(const WEnvironment& env);

    private:
        WLineEdit* nameEdit_;
        WText* greeting_;

        void greet();
    };


}
#endif //CLIENT_H
