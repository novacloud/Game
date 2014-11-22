//
//  DatabaseControl.cpp
//  SimpleGame
//
//  Created by takashi-fukui on 2014/11/22.
//
//

#include "DatabaseControl.h"

USING_NS_CC;

DatabaseControl::DatabaseControl()
{
    
}


void DatabaseControl::init()
{
    auto filePathTo = FileUtils::getInstance()->getWritablePath();
    filePathTo.append("gamedata.db");
    
    log("%s", filePathTo.c_str());
    
    // データベースファイルがあるかチェック
    if(!FileUtils::getInstance()->isFileExist(filePathTo.c_str()))
    {
        log("first start database copy");
        
        // 存在しなければリソースにあるDBをコピー
        FILE *fp;
        if( (fp = fopen(filePathTo.c_str(), "wb")) == NULL )
        {
            log("can not create file %s", filePathTo.c_str());
            return;
        }
        
        std::string filePathFrom = FileUtils::getInstance()->fullPathForFilename("gamedata.db");
        Data data = FileUtils::getInstance()->getDataFromFile(filePathFrom.c_str());
        
        fwrite(data.getBytes(), data.getSize(), 1, fp);
        
        fclose(fp);
    }
}


bool DatabaseControl::open()
{
    auto filePath = FileUtils::getInstance()->getWritablePath();
    filePath.append("gamedata.db");
    
    //OPEN
    auto status = sqlite3_open(filePath.c_str(), &useDataBase);
    
    //ステータスが0以外の場合はエラーを表示
    if (status != SQLITE_OK)
    {
        log("opne failed : %s", errorMessage);
        return false;
    }
    
    return true;
}


void DatabaseControl::close()
{
    sqlite3_close(useDataBase);
}


void DatabaseControl::insertRecord(int score)
{
    if( useDataBase )
    {
        auto sql = StringUtils::format("INSERT INTO record (score) VALUES (%d)", score);
        auto status = sqlite3_exec(useDataBase, sql.c_str() , NULL, NULL, &errorMessage);
    
        if( status != SQLITE_OK )
            log("insert failed : %s", errorMessage);
    }
}


void DatabaseControl::selectRecord(std::vector<int> *record)
{
    if( useDataBase )
    {
        sqlite3_stmt* stmt;
        auto sql = StringUtils::format("SELECT score FROM record ORDER BY score DESC LIMIT 10");
        sqlite3_prepare(useDataBase, sql.c_str(), (int)sql.size(), &stmt, NULL);
        
        int status;
        while( (status = sqlite3_step(stmt)) == SQLITE_ROW )
        {
            record->push_back(sqlite3_column_int(stmt, 0));
        }
        if(status != SQLITE_DONE )
        {
            log("select failed");
        }
        
        sqlite3_finalize(stmt);
    }
}