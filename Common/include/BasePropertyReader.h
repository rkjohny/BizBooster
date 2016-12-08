/*
 * TradexConfigReader.h
 *
 *  Created on: Oct 12, 2016
 *      Author: rezaul
 */

#ifndef BASECONFIGREADER_H_
#define BASECONFIGREADER_H_

#include <map>
#include <string>
#include "SharedObject.h"
#include "Disposable.h"
#include "AppException.h"
#include "AppDef.h"
#include "ConfigReader.h"

namespace Common {
    using namespace std;

    class BasePropertyReader : public ConfigReader {
    public:
        string GetValueOf(const string& key) override;

        void ReloadFile() throw (AppException) override;

        void SetFile(const string& fileName) throw (AppException) override;

    protected:
        BasePropertyReader();
        virtual ~BasePropertyReader();

        void LoadFile(const string& fileName) throw (AppException);
        void Dispose() override;

    private:
        map< string, string > m_properties;
        string m_fileName;

        NON_COPY_NON_ASSIGN_ABLE(BasePropertyReader);
    };

} /* namespace Common */

#endif /* BASECONFIGREADER_H_ */
