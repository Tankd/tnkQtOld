#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <engine.h>
#include "book.h"

#include <QSqlField>


using namespace testing;



class UnicornTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(":memory:");
        db.open();
        m_engine = new unicorn::Engine(db );
        m_engine->createTable(Author::staticMetaObject);
        m_engine->createTable(Book::staticMetaObject);

    }
    virtual void TearDown()
    {
        m_engine->getDb().close();
        delete m_engine;
        m_engine = nullptr;
    }

    unicorn::Engine *m_engine = nullptr;
};


TEST_F(UnicornTest, registerType)
{
    QSqlRecord record = m_engine->getDb().record( m_engine->getTableName( Author::staticMetaObject.className()));
    ASSERT_EQ(record.field("id").type(), QVariant::Int);
    ASSERT_EQ(record.field("name").type(), QVariant::String);

    record = m_engine->getDb().record( m_engine->getTableName( Book::staticMetaObject.className()));
    ASSERT_EQ(record.field("id").type(), QVariant::Int);
    ASSERT_EQ(record.field("isbn").type(), QVariant::String);
    ASSERT_EQ(record.field("pageCount").type(), QVariant::Int);
    ASSERT_EQ(record.field("author").type(), QVariant::Int);
}


TEST_F(UnicornTest, insert)
{
    Author *author = new Author();
    author->set_name("Asimov");

    Book *book = new Book();
    book->set_author( author);

    m_engine->create(book);

    ASSERT_NE( author->get_id(), -1);
    ASSERT_NE( book->get_id(), -1);
}

TEST_F(UnicornTest, get){
    Author *author = new Author();
    author->set_name("Asimov");

    Book *book = new Book();
    book->set_author( author);
    book->set_title("Fondation");
    book->set_isbn("97841531531");
    book->set_pageCount(452);

    m_engine->create(book);



    Book *selectedBook = m_engine->get<Book>( book->get_id());

    ASSERT_EQ( selectedBook->get_id(), book->get_id());
    ASSERT_EQ( selectedBook->get_title(), book->get_title());
    ASSERT_EQ( selectedBook->get_isbn(), book->get_isbn());
    ASSERT_EQ( selectedBook->get_pageCount(), book->get_pageCount());
    ASSERT_EQ( selectedBook->get_author()->get_id(), book->get_author()->get_id());
    ASSERT_EQ( selectedBook->get_author()->get_name(), book->get_author()->get_name());
}


TEST_F(UnicornTest, get_condition){

    Author *author = new Author();
    author->set_name("Asimov");

    Book *book = new Book();
    book->set_author( author);
    book->set_title("Fondation");
    book->set_isbn("97841531531");
    book->set_pageCount(452);

    m_engine->create(book);


    /*******************************************/
    QList<Book *> selectedBooks = m_engine->getAll<Book>( "title = 'Fondation'");

    ASSERT_NE(selectedBooks.count(), 0);

    Book *selectedBook = selectedBooks.first();

    ASSERT_EQ( selectedBook->get_id(), book->get_id());
    ASSERT_EQ( selectedBook->get_title(), book->get_title());
    ASSERT_EQ( selectedBook->get_isbn(), book->get_isbn());
    ASSERT_EQ( selectedBook->get_pageCount(), book->get_pageCount());
    ASSERT_EQ( selectedBook->get_author()->get_id(), book->get_author()->get_id());
    ASSERT_EQ( selectedBook->get_author()->get_name(), book->get_author()->get_name());


}

TEST_F(UnicornTest, update)
{
    Author *author = new Author();
    author->set_name("Asimov");
    m_engine->create( author);

    author->set_name("Tolkien");
    m_engine->update( author);

    Author *resultAuthor = m_engine->get<Author>( author->get_id());
    ASSERT_EQ( resultAuthor->get_id(), author->get_id());

    ASSERT_EQ( resultAuthor->get_name(), "Tolkien");
}

TEST_F(UnicornTest, del)
{
    Author *author = new Author();
    author->set_name("Asimov");
    m_engine->create( author);

    int id = author->get_id();

    m_engine->remove( author);
    delete author;

    author = m_engine->get<Author>( id);

    ASSERT_EQ( author, nullptr);
}

