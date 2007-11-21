# PyDia C++ DAO Code Generation from UML Diagram
# Copyright (c) 2007 Ikaro Games <www.ikarogames.com>
#
# Version: 1.0
#
# Based on PyDia Code Generation from UML Diagram
# Copyright (c) 2005  Hans Breuer <hans@breuer.org>
#
#    This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 2 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program; if not, write to the Free Software
#   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.


import os, sys, dia
from string import Template

class Klass :
	def __init__ (self, name) :
		self.name = name
		self.attributes = {}
		self.operations = {}
		self.comment = ""
	def AddAttribute(self, name, type, visibility) :
		self.attributes[name] = (type, visibility)
	def AddOperation(self, name, type, visibility, params) :
		self.operations[name] = (type, visibility, params)
	def SetComment(self, s) :
		self.comment = s

class ObjRenderer :
	"Implements the Object Renderer Interface and transforms diagram into its internal representation"
	def __init__ (self) :
		# an empty dictionary of classes
		self.klasses = {}
		self.filename = ""
		self.path = ""
		self.name = ""
		self.ext = ""
	def begin_render (self, data, filename) :
		self.filename = filename
		self.path = os.path.dirname(filename)
		(self.name, self.ext) = os.path.splitext(os.path.basename(self.filename))
		for layer in data.layers :
			# for the moment ignore layer info. But we could use this to spread accross different files
			for o in layer.objects :
				if o.type.name == "UML - Class" :
					#print o.properties["name"].value
					k = Klass (o.properties["name"].value)
					k.SetComment(o.properties["comment"].value)
					for op in o.properties["operations"].value :
						# op : a tuple with fixed placing, see: objects/UML/umloperations.c:umloperation_props
						# (name, type, comment, stereotype, visibility, inheritance_type, class_scope, params)
						params = []
						for par in op[8] :
							# par : again fixed placement, see objects/UML/umlparameter.c:umlparameter_props
							params.append((par[0], par[1]))
						k.AddOperation (op[0], op[1], op[4], params)
					#print o.properties["attributes"].value
					for attr in o.properties["attributes"].value :
						# see objects/UML/umlattributes.c:umlattribute_props
						#print "\t", attr[0], attr[1], attr[4]
						k.AddAttribute(attr[0], attr[1], attr[4])
					self.klasses[o.properties["name"].value] = k
				elif o.type.name == "UML - Generalization" :
					# could setup inheritance here
					pass
				elif o.type.name == "UML - Association" :
					# should already have got attributes relation by names
					pass
				# other UML objects which may be interesting
				# UML - Note, UML - LargePackage, UML - SmallPackage, UML - Dependency, ...
	def end_render(self) :
		# without this we would accumulate info from every pass
		self.attributes = {}
		self.operations = {}


class DAORenderer(ObjRenderer) :
	def __init__(self) :
		ObjRenderer.__init__(self)

#####################################################################################

	def licensed(self) :
		string = "/******************************************************************************\n\
* Copyright (C) 2007 - Ikaro Games   www.ikarogames.com                       *\n\
*                                                                             *\n\
* This program is free software; you can redistribute it and/or               *\n\
* modify it under the terms of the GNU General Public License                 *\n\
* as published by the Free Software Foundation; either version 2              *\n\
* of the License, or (at your option) any later version.                      *\n\
*                                                                             *\n\
* This program is distributed in the hope that it will be useful,             *\n\
* but WITHOUT ANY WARRANTY; without even the implied warranty of              *\n\
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *\n\
* GNU General Public License for more details.                                *\n\
*                                                                             *\n\
* You should have received a copy of the GNU General Public License           *\n\
* along with this program; if not, write to the Free Software                 *\n\
* Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. *\n\
*                                                                             *\n\
*                                                                             *\n\
*       generated by dia/DAOcodegen.py                                        *\n\
*       Version: 1.0                                                          *\n\
******************************************************************************/\n\n\n"
		return string

	def interfaceName(self, string) :
		cad = string
		cad = cad.lower()
 		cad = cad.replace("_", " ")
		cad = cad.title()
		cad = cad.replace(" ", "")
		cad = "I" + cad
		return cad

	def className(self, string) :
		cad = string
		cad = cad.lower()
 		cad = cad.replace("_", " ")
		cad = cad.title()
		cad = cad.replace(" ", "")
		cad = "C" + cad
		return cad

	def attributeName(self, cadena) :
		cad = cadena
		cad = cad.lower()
 		cad = cad.replace("_", " ")
		cad = cad.title()
		cad = cad.replace(" ", "")
		return cad

##########################     IDAOFactory.h   #######################################

	def headIDAOFactoryH(self) :
		head = self.licensed() + \
	        	   "#ifndef __IDAOFactory_H__\n#define __IDAOFactory_H__\n\n\n"
		return head
	
	def bodyIDAOFactoryH(self) :
		body = "\n\
class IDAOFactory\n\
{\n\
public:\n    virtual ~IDAOFactory() {}\n"
		return body
	
	def tailIDAOFactoryH(self) :
		tail = "\n\n};\n\n\n#endif //__IDAOFactory_H__\n\n"
		return tail

	def stringsIDAOFactoryH(self, name, includes, metods) :
		includes = includes + "#include \"" + name + "DAO.h\"\n"
		metods = metods + "\n\
    virtual " + name + "DAO* get" + name + "DAO() = 0;\n"
		return includes, metods

	def createIDAOFactoryH(self) :
		metods_H = ""
		includes_H = ""
		# declaration
		for sk in self.klasses.keys() :
			interface_Name = self.interfaceName(sk)
			includes_H, metods_H = self.stringsIDAOFactoryH(interface_Name, \
								includes_H, metods_H)
		cad = os.path.join(self.path, "IDAOFactory.h")
		file = open(cad, "w")
		code = self.headIDAOFactoryH() + \
				includes_H + \
				self.bodyIDAOFactoryH() + \
				metods_H + self.tailIDAOFactoryH()
		file.write(code)
		file.close()

##########################     CDAOFactorySqlite.h   ##################################

	def headCDAOFactorySqliteH(self) :
		head = self.licensed() + \
	        	   "#ifndef __CDAOFactorySqlite_H__\n\
#define __CDAOFactorySqlite_H__\n\
\n\
#include <sqlite3.h>\n\
\n\
#include \"IDAOFactory.h\"\n"
		return head
	
	def bodyCDAOFactorySqliteH(self) :
		body = "\n\
class CDAOFactorySqlite : public IDAOFactory\n\
{\n\
friend class CDAOAbstractFactory;\n\
\n\
private:\n\
\n\
    static CDAOFactorySqlite* m_instance;\n\
    static sqlite3 *m_dataBase;\n\
\n\
    CDAOFactorySqlite();\n\
\n\
    static CDAOFactorySqlite* getInstance();\n\
\n\
public:\n\
\n\
    virtual ~CDAOFactorySqlite();\n"
		return body
	
	def tailCDAOFactorySqliteH(self) :
		tail = "\n\n};\n\n\n#endif //__CDAOFactorySqlite_H__\n\n"
		return tail

	def stringsCDAOFactorySqliteH(self, name, includes, metods) :
		includes = includes + "#include \"" + name + "DAO.h\"\n"
		metods = metods + "\n\
    virtual " + name + "DAO* get" + name + "DAO();\n"
		return includes, metods

	def createCDAOFactorySqliteH(self) :
		metods_H = ""
		includes_H = ""
		# declaration
		for sk in self.klasses.keys() :
			interface_Name = self.interfaceName(sk)
			includes_H, metods_H = self.stringsCDAOFactorySqliteH(interface_Name, \
								includes_H, metods_H)
		cad = os.path.join(self.path, "CDAOFactorySqlite.h")
		file = open(cad, "w")
		code = self.headCDAOFactorySqliteH() + \
				includes_H + \
				self.bodyCDAOFactorySqliteH() + \
				metods_H + self.tailCDAOFactorySqliteH()
		file.write(code)
		file.close()



#############################    CClass.h  ######################################

	def writeCClassH(self, name, attributes) :
		head = self.licensed() + "#ifndef __" + name + "_H__\n\
#define __" + name + "_H__\n\
\n\
#include <string>\n\
\n\
using namespace std;\n\
\n\
\n\
class " + name + "\n\
{\n\
public:\n\
\n\
    " + name + "();\n\
    " + name + "("
		constructor = ""
		sets = ""
		gets = ""
		atrib = ""
		body1 = ");\n    ~" + name + "();\n\n"
		body2 = "\nprivate:\n"
		tail = "};\n\n#endif // __" + name + "_H__ \n\n"
		coma = ""
		cont = 0
		for a in attributes :
			at = self.attributeName(a)
			if cont < 2 :
				constructor = constructor + coma + "string " + at
				coma = ", "
				cont = cont + 1
			else :
				constructor = constructor + coma + "\n        string " + at
				cont = 1
			sets = sets + "    void set" + at + "(string " + at + ");\n"
			gets = gets + "    const string* get" + at + "();\n"
			atrib = atrib + "    string *m_" + at + ";\n"
		cad = os.path.join(self.path, name + ".h")
		file = open(cad, "w")
		code = head + constructor + body1 + sets + \
			 gets + body2 + atrib + tail
		file.write(code)
		file.close()

############################    CClass.cpp   #####################################

	def writeCClassCPP(self, name, attributes) :
		head = self.licensed() + "#include <string>\n\n#include \"" + \
		name + ".h\"\n\n" + \
		name + "::" + name + "()\n{\n"
		body1 = "}\n\n" + name + "::" + name + "("
		body2 = ")\n{\n"
		body3 = "}\n\n" + name + "::~" + name + "()\n{\n"
		body4 = "}\n\n"
		constDef = ""
		paramConst = ""
		constParam = ""
		dest = ""
		sets = ""
		gets = ""
		coma = ""
		cont = 0
		for a in attributes :
			at = self.attributeName(a)
			constDef = constDef + "    m_" + at + " = new std::string(\"\");\n"
			constParam = constParam + "    m_" + at + " = new std::string(" + at + ");\n"
			dest = dest + "    delete m_" + at + ";\n"
			sets = sets + "void " + name + "::set" + at + "(string " + at + ")\n\
{\n\
    delete m_" + at + ";\n\
    m_" + at + " = new string(" + at + ");\n\
}\n\n"
			gets = gets + "const string* " + name + "::get" + at + "()\n\
{\n\
    return m_" + at + ";\n\
}\n\n"
			if cont < 2 :
				paramConst = paramConst + coma + "string " + at
				coma = ", "
				cont = cont + 1
			else :
				paramConst = paramConst + coma + "\n        string " + at
				cont = 1
		cad = os.path.join(self.path, name + ".cpp")
		file = open(cad, "w")
		code = head + constDef + body1 + paramConst + body2 + constParam + \
			 body3 + dest + body4 + sets + gets
		file.write(code)
		file.close()

	def createCClassH(self) :
		# declaration
		for sk in self.klasses.keys() :
			class_Name = self.className(sk)
			k = self.klasses[sk]
			# first sort by visibility
			ops = [[], [], [], []]
			for so in k.operations.keys() :
				t, v, p = k.operations[so]
				ops[v].append((t,so,p))
			vars = [[], [], [], []]
			for sa in k.attributes.keys() :
				t, v = k.attributes[sa]
				vars[v].append((t, sa))
			visibilities = ("public:", "private:", "protected:", "/* implementation: */")
			for v in [0,2,1,3] :
				if len(ops[v]) == 0 and len(vars[v]) == 0 :
					continue
				#fdaofactory.write ("%s\n" % visibilities[v])
				for op in ops[v] :
					# detect ctor/dtor
					so = ""
					if sk == op[1] or ("~" + sk) == op[1] :
						so = "\t%s (" % (op[1])
					else :
						so = "\t%s %s (" % (op[0], op[1])
					#fdaofactory.write (so)
					# align parameters with the opening brace
					n = len(so)
					i = 0
					m = len(op[2]) - 1
					for p in op[2] :
						linefeed = ",\n\t" + " " * (n - 1) 
						if i == m :
							linefeed = ""
						#fdaofactory.write ("%s %s%s" % (p[1], p[0], linefeed))
						i = i + 1
					#fdaofactory.write(");\n")
				attrib = []
				for var in vars[v] :
					attrib.append(var[1])
			self.writeCClassH(class_Name, attrib)
			self.writeCClassCPP(class_Name, attrib)
			del attrib

############################    CClassDAOSqlite.h  ##################################

	def writeCClassDAOSqliteH(self, name, attrib) :
		tail = "\n};\n#endif // __${CLASSNAME}DAOSqlite_H__\n"
		finds = "\n\n"
		for a in attrib :
			finds = finds + "    ${CLASSNAME}* findBy" + \
			self.attributeName(a) + "(string " + self.attributeName(a) +");\n"
		template = Template(self.licensed() + "#ifndef __${CLASSNAME}DAOSqlite_H__\n\
#define __${CLASSNAME}DAOSqlite_H__\n\
\n\
#include <sqlite3.h>\n\
\n\
#include \"${CLASSNAME}DAOSqliteEntity.h\"\n\
\n\
class ${CLASSNAME}DAOSqlite : public ${CLASSNAME}DAOSqliteEntity\n\
{\n\
\n\
public:\n\
    ${CLASSNAME}DAOSqlite(sqlite3 *dataBase);\n\
    virtual ~${CLASSNAME}DAOSqlite();" + finds + tail)

		cad = os.path.join(self.path, name + "DAOSqlite.h")
		file = open(cad, "w")
		code = template.substitute(CLASSNAME=name)
		file.write(code)
		file.close()

###############################  CClassDAOSqliteEntity.h   ###########################

	def writeCClassDAOSqliteEntityH(self, name, i_name) :
		tail = "\nprotected:\n\
    ${CLASSNAME}* loadRegister(string sql);\n\
    vector<${CLASSNAME}*> * loadVector(string sql);\n\
\n\
private:\n\
    sqlite3 *m_dataBase;\n\
\n\
    bool exec(string sql);\n\
    static int callbackRegister(void *object, int nColumns, char **vColumn, char **sColumn );\n\
    static int callbackVector(void *object, int nColumns, char **vColumn, char **sColumn );\n\
\n};\n#endif // __${CLASSNAME}DAOSqliteEntity_H__\n"
		template = Template(self.licensed() + "#ifndef __${CLASSNAME}DAOSqliteEntity_H_\n\
#define __${CLASSNAME}DAOSqliteEntity_H_\n\
\n\
#include <string>\n\
#include <vector>\n\
\n\
#include \"${INTERFACENAME}DAO.h\"\n\
\n\
using namespace std;\n\
\n\n\
class ${CLASSNAME}DAOSqliteEntity : public ${INTERFACENAME}DAO\n\
{\n\
\n\
public:\n\
    ${CLASSNAME}DAOSqliteEntity(sqlite3 *dataBase);\n\
    virtual ~${CLASSNAME}DAOSqliteEntity();\n\
\n\
    virtual bool deleteReg(${CLASSNAME} * elem);\n\
    virtual bool insert(${CLASSNAME} * elem);\n\
    virtual bool update(${CLASSNAME} * elem);\n" + tail)

		cad = os.path.join(self.path, name + "DAOSqliteEntity.h")
		file = open(cad, "w")
		code = template.substitute(CLASSNAME=name, INTERFACENAME=i_name)
		file.write(code)
		file.close()

############################    IClassDAO.h  ##################################

	def writeIClassDAOH(self, name, i_name, attrib) :
		tail = "\n};\n#endif // __${INTERFACENAME}DAO_H__\n"
		finds = "\n\n"
		for a in attrib :
			finds = finds + "    virtual ${CLASSNAME}* findBy" + \
			self.attributeName(a) + "(string " + self.attributeName(a) +") {return NULL;}\n"
		template = Template(self.licensed() + "#ifndef __${INTERFACENAME}DAO_H__\n\
#define __${INTERFACENAME}DAO_H__\n\
\n\
#include <string>\n\
#include <vector>\n\
\n\
#include \"${CLASSNAME}.h\"\n\
\n\
class ${INTERFACENAME}DAO\n\
{\n\
\n\
public:\n\
    virtual ~${INTERFACENAME}DAO() {}\n\
\n\
    virtual bool deleteReg(${CLASSNAME} * elem) =0;\n\
    virtual bool insert(${CLASSNAME} * elem) =0;\n\
    virtual bool update(${CLASSNAME} * elem) =0;\n\n" + finds + tail)

		cad = os.path.join(self.path, i_name + "DAO.h")
		file = open(cad, "w")
		code = template.substitute(CLASSNAME=name, INTERFACENAME=i_name)
		file.write(code)
		file.close()

############################    CClassDAOSqlite.cpp  ##################################

	def writeCClassDAOSqliteCPP(self, name, t_name, attrib) :
		head = "#include <sqlite3.h>\n\n\
#include \"${CLASSNAME}DAOSqlite.h\"\n\
\n\
\n\
${CLASSNAME}DAOSqlite::${CLASSNAME}DAOSqlite(sqlite3 *dataBase)\n\
:${CLASSNAME}DAOSqliteEntity(dataBase)\n\
{\n\
\n\
}\n\
\n\
\n\
${CLASSNAME}DAOSqlite::~${CLASSNAME}DAOSqlite()\n\
{\n\
\n\
}\n\n"
		finds = "\n\n"
		for a in attrib :
			aux = self.attributeName(a)
			finds = finds + "${CLASSNAME}* ${CLASSNAME}DAOSqlite::findBy"+aux+"(string val)\n\
{\n\
    ${CLASSNAME} *destiny = NULL;\n\
    string sql = \"SELECT * FROM "+t_name+"\";\n\
    const char *aux = val.c_str();\n\
    if (strcmp(aux,\"\") != 0) {\n\
        sql = sql + \" WHERE "+a+"='\" + aux + \"'\";\n\
    }\n\
    destiny = loadRegister(sql);\n\
    return destiny;\n\
}\n\
\n\
//vector<${CLASSNAME}*>* ${CLASSNAME}DAOSqlite::findVectorBy"+aux+"(string val)\n\
//{\n\
//    vector<${CLASSNAME} *> *destiny = NULL;\n\
//    string sql = \"SELECT * FROM "+t_name+"\";\n\
//    const char *aux = val.c_str();\n\
//    if (strcmp(aux,\"\") != 0) {\n\
//        sql = sql + \" WHERE "+a+"='\" + aux + \"'\";\n\
//    }\n\
//    destiny = loadVector(sql);\n\
//    return destiny;\n\
//}\n\n"
		
		template = Template(self.licensed() + head + finds)

		cad = os.path.join(self.path, name + "DAOSqlite.cpp")
		file = open(cad, "w")
		code = template.substitute(CLASSNAME=name)
		file.write(code)
		file.close()


	def createClassDAO_H_CPP(self) :
		
		# declaration
		for sk in self.klasses.keys() :
			class_Name = self.className(sk)
			t_Name = sk
			interface_Name = self.interfaceName(sk)
			k = self.klasses[sk]
			# first sort by visibility
			ops = [[], [], [], []]
			for so in k.operations.keys() :
				t, v, p = k.operations[so]
				ops[v].append((t,so,p))
			vars = [[], [], [], []]
			for sa in k.attributes.keys() :
				t, v = k.attributes[sa]
				vars[v].append((t, sa))
			visibilities = ("public:", "private:", "protected:", "/* implementation: */")
			for v in [0,2,1,3] :
				if len(ops[v]) == 0 and len(vars[v]) == 0 :
					continue
				#fdaofactory.write ("%s\n" % visibilities[v])
				for op in ops[v] :
					# detect ctor/dtor
					so = ""
					if sk == op[1] or ("~" + sk) == op[1] :
						so = "\t%s (" % (op[1])
					else :
						so = "\t%s %s (" % (op[0], op[1])
					#fdaofactory.write (so)
					# align parameters with the opening brace
					n = len(so)
					i = 0
					m = len(op[2]) - 1
					for p in op[2] :
						linefeed = ",\n\t" + " " * (n - 1) 
						if i == m :
							linefeed = ""
						#fdaofactory.write ("%s %s%s" % (p[1], p[0], linefeed))
						i = i + 1
					#fdaofactory.write(");\n")
				attrib = []
				for var in vars[v] :
					if var[1].find("X_") != -1 :
						attrib.append(var[1])
			self.writeCClassDAOSqliteH(class_Name, attrib)
			self.writeCClassDAOSqliteEntityH(class_Name, interface_Name)
			self.writeIClassDAOH(class_Name, interface_Name, attrib)
			self.writeCClassDAOSqliteCPP(class_Name, t_Name, attrib)
			del attrib

############################    CDAOFactorySqlite.cpp  ##################################

	def headCDAOFactorySqliteCPP(self) :
		head = self.licensed() + \
	        	   "#include <sqlite3.h>\n\n#include \"CDAOFactorySqlite.h\"\n"
		return head
	
	def bodyCDAOFactorySqliteCPP(self) :
		body = "\n\nsqlite3 * CDAOFactorySqlite::m_dataBase = NULL;\n\
\n\
CDAOFactorySqlite::CDAOFactorySqlite()\n\
{\n\
//    Se lee el nombre del fichero que contiene la bbdd\n\
//    const char *fileDB = CGestorOpciones::opcionCadena( \"BaseDeDatos\",\n\
//                              \"fichero\", \"data/bbdd/PFBaseDatos.sql3\" );\n\
    const char *fileDB = \"data/bbdd/dbtest.sql3\";\n\
    if (sqlite3_open(fileDB, &m_dataBase) != SQLITE_OK) {\n\
        sqlite3_close(m_dataBase);\n\
        m_dataBase = NULL;\n\
        //CGestorLog::excepcion( \"No se pudo abrir el fichero de la bbdd: \\\"%s\\\" --> \\\"%s\\\"\", ficheroBD, sqlite3_errmsg(m_baseDeDatos) );\n\
    }\n\
    //CGestorLog::info( \"Gestor de Base de Datos inicializado: <-- \\\"%s\\\"\", ficheroBD );\n\
}\n\
\n\
CDAOFactorySqlite::~CDAOFactorySqlite()\n\
{\n\n}\n\n\
CDAOFactorySqlite* CDAOFactorySqlite::getInstance()\n\
{\n\
    static CDAOFactorySqlite instance;\n\
\n\
    return &instance;\n\
}\n\n"
		return body
	
	def stringsCDAOFactorySqliteCPP(self, c_name, i_name, includes, metods) :
		includes = includes + "#include \"" + c_name + "DAOSqlite.h\"\n"
		metods = metods + i_name + "DAO* CDAOFactorySqlite::get" + \
		i_name + "DAO()\n\
{\n\
    static " + c_name + "DAOSqlite dao(m_dataBase);\n\
    return &dao;\n\
}\n\n"
		return includes, metods

	def createCDAOFactorySqliteCPP(self) :
		metods_H = ""
		includes_H = ""
		# declaration
		for sk in self.klasses.keys() :
			c_Name = self.className(sk)
			i_Name = self.interfaceName(sk)
			includes_H, metods_H = self.stringsCDAOFactorySqliteCPP \
					(c_Name, i_Name, includes_H, metods_H)
		cad = os.path.join(self.path, "CDAOFactorySqlite.cpp")
		file = open(cad, "w")
		code = self.headCDAOFactorySqliteCPP() + \
				includes_H + \
				self.bodyCDAOFactorySqliteCPP() + metods_H
		file.write(code)
		file.close()


########################    CClassDAOSqliteEntity.cpp  ##############################

	def deleteReg(self, name, t_name, attKey) :
		keyName = self.attributeName(attKey)
		result = "bool "+name+"DAOSqliteEntity::deleteReg("+name+" * elem)\n\
{\n\
    std::string sql(\"DELETE FROM "+t_name+" WHERE "+attKey+"='\");\n\
    sql = sql + elem->get"+keyName+"()->c_str() + \"'\";\n\
    return exec(sql);\n\
}\n\n\n"
		return result
		
	def insert(self, name, t_name, attKey, att) :
		keyName = self.attributeName(attKey)
		result = "bool "+name+"DAOSqliteEntity::insert("+name+" * elem)\n\
{\n\
    std::string sql(\"INSERT INTO "+t_name+" \\\n\
                    ("+attKey
		cont = 1
		columns = ""
		values = ""
		for a in att :
			attName = self.attributeName(a)
			if cont == 3 :
				columns = columns + ",\\\n                     " + a
				cont = 1
			else :
				columns = columns + "," + a
				cont = cont + 1
			values = values + \
			"    sql = sql + \",'\" + elem->get"+attName+"()->c_str() + \"'\";\n"
		result = result + columns + ") VALUES (\");\n\
    sql = sql + \" '\" + elem->get"+keyName+"()->c_str() + \"'\";\n"+values+"\
    sql = sql + \")\";\n\
    return exec(sql);\n\
}\n\n\n"
		return result

	def update(self, name, t_name, attKey, att) :
		keyName = self.attributeName(attKey)
		result = "bool "+name+"DAOSqliteEntity::update("+name+" * elem)\n\
{\n\
    std::string sql(\"UPDATE "+t_name+" SET\");\n\n"
		sets = ""
		first = 1
		for a in att :
			attName = self.attributeName(a)
			if first == 1 :
				first = 0
				sets = "    sql = sql + \"  "+a+"='\"\n\
               + elem->get"+attName+"()->c_str() + \"'\";\n"
			else :
				sets = sets + "    sql = sql + \",  "+a+"='\"\n\
               + elem->get"+attName+"()->c_str() + \"'\";\n"
		result = result + sets + "    sql = sql + \"  WHERE "+attKey+"='\"\n\
              + elem->get"+keyName+"()->c_str() + \"'\";\n\
\n\
    return exec(sql);\n\
}\n\n\n"
		return result

	def callbackRegister(self, name, t_name, attKey, att) :
		keyName = self.attributeName(attKey)
		result = "int "+name+"DAOSqliteEntity::callbackRegister\n\
    (void *object, int nColumns, char **vColumn, char **sColumn)\n\
{\n\
    int error = 1;\n\
    if (object != NULL) {\n\
        "+name+" *destiny = ("+name+"*)object;\n\
        for (int i = 0; i < nColumns; i++) {\n"
		iff = "            if (strcmp(sColumn[i], \""+attKey+"\") == 0) {\n\
                destiny->set"+keyName+"(std::string(vColumn[i]));\n\
            }"
		for a in att :
			attName = self.attributeName(a)
			iff = iff + " else if (strcmp(sColumn[i], \""+a+"\") == 0) {\n\
                destiny->set"+attName+"(std::string(vColumn[i]));\n\
            }"
		result = result + iff + "\n        }\n\
        error = 0; // All is ok\n\
    }\n\
    return error;\n\
}\n\n\n"
		return result

	def callbackVector(self, name, t_name, attKey, att) :
		keyName = self.attributeName(attKey)
		result = "int "+name+"DAOSqliteEntity::callbackVector\n\
    (void *object, int nColumns, char **vColumn, char **sColumn)\n\
{\n\
    if (object != NULL) {\n\
        std::vector<"+name+"*> *container;\n\
        container = (std::vector<"+name+"*> *)object;\n\
        "+name+" *destiny = new "+name+"();\n\
        for (int i = 0; i < nColumns; i++) {\n"
		iff = "            if (strcmp(sColumn[i], \""+attKey+"\") == 0) {\n\
                destiny->set"+keyName+"(std::string(vColumn[i]));\n\
            }"
		for a in att :
			attName = self.attributeName(a)
			iff = iff + " else if (strcmp(sColumn[i], \""+a+"\") == 0) {\n\
                destiny->set"+attName+"(std::string(vColumn[i]));\n\
            }"
		result = result + iff + "\n        }\n\
        container->push_back(destiny);\n\
    }\n\
    return 0; // All is ok\n\
}\n\n\n"
		return result

	def writeCClassDAOSqliteEntityCPP(self, name, t_name, attKey, att) :
		head = "#include <sqlite3.h>\n\
\n\
#include \"${CLASSNAME}DAOSqliteEntity.h\"\n\
\n\
\n\
${CLASSNAME}DAOSqliteEntity::${CLASSNAME}DAOSqliteEntity(sqlite3 *dataBase)\n\
{\n\
    m_dataBase = dataBase;\n\
}\n\
\n\
\n\
${CLASSNAME}DAOSqliteEntity::~${CLASSNAME}DAOSqliteEntity()\n\
{\n\
\n\
}\n\
\n\
\n\
${CLASSNAME}* ${CLASSNAME}DAOSqliteEntity::loadRegister(string sql)\n\
{\n\
    char *msgError = NULL;\n\
    ${CLASSNAME} *destiny = new ${CLASSNAME}();\n\
    if (sqlite3_exec(m_dataBase, sql.c_str(), callbackRegister, destiny, &msgError)\n\
        != SQLITE_OK) {\n\
        //CGestorLog::error( \"Error al ejecutar la sentencia SQL: \\\"%s\\\" --> \\\"%s\\\"\", sentenciaSQL, msgError );\n\
        sqlite3_free(msgError);\n\
    }\n\
    return destiny;\n\
}\n\
\n\
\n\
vector<${CLASSNAME}*> * ${CLASSNAME}DAOSqliteEntity::loadVector(string sql)\n\
{\n\
    char *msgError = NULL;\n\
    vector<${CLASSNAME} *> *container = new vector<${CLASSNAME} *>;\n\
    if (sqlite3_exec(m_dataBase, sql.c_str(), callbackVector, container, &msgError)\n\
        != SQLITE_OK) {\n\
        //CGestorLog::error( \"Error al ejecutar la sentencia SQL: \\\"%s\\\" --> \\\"%s\\\"\", sentenciaSQL, msgError );\n\
        sqlite3_free(msgError);\n\
    }\n\
    return container;\n\
}\n\
\n\
\n\
bool ${CLASSNAME}DAOSqliteEntity::exec(string sql)\n\
{\n\
    char *msgError = NULL;\n\
    bool correct = true;\n\
    if (sqlite3_exec(m_dataBase, sql.c_str(), NULL, NULL, &msgError)\n\
        != SQLITE_OK) {\n\
        //CGestorLog::error( \"Error al ejecutar la sentencia SQL: \\\"%s\\\" --> \\\"%s\\\"\", sql.c_str(), msgError );\n\
        sqlite3_free(msgError);\n\
        correct = false;\n\
    }\n\
    return correct;\n\
}\n\n\n"
		s_deleteReg = self.deleteReg(name, t_name, attKey)
		s_insert = self.insert(name, t_name, attKey, att)
		s_update = self.update(name, t_name, attKey, att)
		s_callbackRegister = self.callbackRegister(name, t_name, attKey, att)
		s_callbackVector = self.callbackVector(name, t_name, attKey, att)
		template = Template(self.licensed() + head + 
		s_deleteReg + s_insert + s_update + s_callbackRegister + s_callbackVector)

		cad = os.path.join(self.path, name + "DAOSqliteEntity.cpp")
		file = open(cad, "w")
		code = template.substitute(CLASSNAME=name)
		file.write(code)
		file.close()

	def createCClassDAOSqliteEntityCPP(self) :
		# declaration
		for sk in self.klasses.keys() :
			class_Name = self.className(sk)
			t_name = sk
			k = self.klasses[sk]
			# first sort by visibility
			ops = [[], [], [], []]
			for so in k.operations.keys() :
				t, v, p = k.operations[so]
				ops[v].append((t,so,p))
			vars = [[], [], [], []]
			for sa in k.attributes.keys() :
				t, v = k.attributes[sa]
				vars[v].append((t, sa))
			visibilities = ("public:", "private:", "protected:", "/* implementation: */")
			for v in [0,2,1,3] :
				if len(ops[v]) == 0 and len(vars[v]) == 0 :
					continue
				#fdaofactory.write ("%s\n" % visibilities[v])
				for op in ops[v] :
					# detect ctor/dtor
					so = ""
					if sk == op[1] or ("~" + sk) == op[1] :
						so = "\t%s (" % (op[1])
					else :
						so = "\t%s %s (" % (op[0], op[1])
					#fdaofactory.write (so)
					# align parameters with the opening brace
					n = len(so)
					i = 0
					m = len(op[2]) - 1
					for p in op[2] :
						linefeed = ",\n\t" + " " * (n - 1) 
						if i == m :
							linefeed = ""
						#fdaofactory.write ("%s %s%s" % (p[1], p[0], linefeed))
						i = i + 1
					#fdaofactory.write(");\n")
				attrib = []
				att = []
				attKey = ""
				for var in vars[v] :
					attrib.append(var[1])
					if var[0].find("PRIMARY") != -1 :
						attKey = var[1]
					else :
						att.append(var[1])
			self.writeCClassDAOSqliteEntityCPP(class_Name, t_name, attKey, att)
			del attrib
			del att

#####################################################################################

	def end_render(self) :
		
		self.createIDAOFactoryH()
		self.createCDAOFactorySqliteH()
		self.createCClassH()
		self.createClassDAO_H_CPP()
		self.createCDAOFactorySqliteCPP()
		self.createCClassDAOSqliteEntityCPP()
		
		ObjRenderer.end_render(self)



# dia-python keeps a reference to the renderer class and uses it on demand
dia.register_export ("PyDia Code Generation (C++ DAO)", "cpp", DAORenderer())
