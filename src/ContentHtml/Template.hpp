/*
 * Hermod - Modular application framework
 *
 * Hermod is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License 
 * version 3 as published by the Free Software Foundation. You
 * should have received a copy of the GNU Lesser General Public
 * License along with this program, see LICENSE file for more details.
 * This program is distributed WITHOUT ANY WARRANTY see README file.
 *
 * The Template layer is based on NLTemplate, an HTML templatnig library
 * for C++. See https://github.com/catnapgames/NLTemplate for the original
 * project.
 *
 * Authors: Tomas Andrle (Original library)
 */
#ifndef CONTENTHTML_TEMPLATE_HPP
#define CONTENTHTML_TEMPLATE_HPP
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

namespace hermod {
    namespace contentHtml {

struct Token {
    int type;
    std::string value;
};


class Tokenizer {
private:
    const char *text;
    long len;
    long pos;
    Token peek;
    bool peeking;
public:
    // Tokenizer will free() the text on exit
    Tokenizer( const char *text );
    ~Tokenizer();
    Token next();
};


class Dictionary {
public:
    std::vector<std::pair<std::string, std::string> > properties;
    
public:
    const std::string find( const std::string & name ) const;
    void set( const std::string & name, const std::string & value );
};


class Output {
public:
    virtual ~Output();
    virtual void print( const std::string & text ) = 0;
};


class Fragment {
public:
    virtual void render( Output & output, const Dictionary & dictionary ) const = 0;
    virtual ~Fragment();
    virtual Fragment *copy() const = 0;
    virtual bool isBlockNamed( const std::string & name ) const;
};


class Text : public Fragment {
private:
    const std::string text;
    
public:
    Text( const std::string & text );
    void render( Output & output, const Dictionary & dictionary ) const;
    Fragment *copy() const;
};


class Property : public Fragment {
private:
    const std::string name;
    
public:
    Property( const std::string & name );
    void render( Output & output, const Dictionary & dictionary ) const;
    Fragment *copy() const;
};


class Block;


class Node : public Fragment, public Dictionary {
public:
    std::vector<Fragment*> fragments;
    
public:
    ~Node();
    Fragment *copy() const;
    void render( Output & output, const Dictionary & dictionary ) const;
    Block & block( const std::string & name ) const;
};


class Block : public Node {
protected:
    const std::string name;
    bool enabled;
    bool resized;
    std::vector<Node*> nodes;
    
public:
    Block( const std::string & name );
    Fragment *copy() const;
    ~Block();
    bool isBlockNamed( const std::string & name ) const;
    void enable();
    void disable();
    void repeat( size_t n );
    Node & operator[]( size_t index );
    void render( Output & output, const Dictionary & dictionary ) const;
};



class OutputStdout : public Output {
public:
    void print( const std::string & text );
};


class OutputString : public Output {
public:
    std::stringstream buf;
    
public:
    void print( const std::string & text );
};


class Loader {
public:
    virtual ~Loader();
    // Returns mallocated memory that the consumer must free()
    virtual const char * load( const char *name ) = 0;
};


class LoaderFile : public Loader {
public:
    const char * load( const char *name );
};



class Template : public Block {
protected:
    Loader & loader;
    
public:
    Template( Loader & loader );
    void clear();
    void load( const char *name );
    void render( Output & output ) const;
    
protected:
    void load_recursive( const char *name, std::vector<Tokenizer*> & files, std::vector<Node*> & nodes );
};


    
    } // namespace contentHtml
} // namespace hermod
#endif
