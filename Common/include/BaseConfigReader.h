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

namespace Common {
    using namespace std;

    class BaseConfigReader : public SharedObject, public Disposable {
    public:
        string GetValueOf(const string& key);

        void ReloadFile() throw (AppException);
        void SetFile(const string& fileName) throw (AppException);

    protected:
        BaseConfigReader();
        ~BaseConfigReader();

        void Dispose() override;
        void LoadFile(const string& fileName) throw (AppException);

    private:

        map< string, string > m_properties;
        string m_fileName;

        BaseConfigReader(BaseConfigReader&) = delete;
        BaseConfigReader& operator=(BaseConfigReader&) = delete;
    };

} /* namespace Common */

#endif /* BASECONFIGREADER_H_ */
