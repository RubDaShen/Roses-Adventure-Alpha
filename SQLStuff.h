#pragma once

#include		<iostream>
#include		<Windows.h>
#include		<sql.h>
#include		<sqlext.h>
#include		<sqltypes.h>
#include		<string>
#include		<thread>
#include		<mutex>



namespace		sql
{
	//	Query status.
	enum	enm_QueryStatus
	{
		NotRunnning			= 0,
		Asking				= 1,
		ReadyToPair			= 2,
		ErrorWhenAsking		= 3,

		GettingInfo			= 4,
		Done				= 5,
		ErrorWhenGetting	= 6,
	};

	//	Function to get the SQL error.
	inline void			ShowSQLError(	unsigned int HandleType		,
										const SQLHANDLE& Handler	)
	{
		const int		BufferSize = 256;
		SQLCHAR			SQLState[BufferSize];
		SQLCHAR			SQLMessage[BufferSize];



		if (	SQL_SUCCESS == SQLGetDiagRecA(HandleType, Handler, 1, SQLState, NULL, SQLMessage, BufferSize, NULL)	)
		{
			std::cout << "Message: " << SQLMessage << "\nSQLSTATE: " << SQLState << std::endl;
		}
	}



	//	Main class SQL Connnector.
	class		SQLConnector
	{
	//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
	//						 Private side !
	//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

	//	-------------------------------------------
	//					Structs
	//	-------------------------------------------
	private:
		struct		SQL_StatementHandler
		{
			//	-------------------------------------------
			//					Variables
			//	-------------------------------------------
			SQLHSTMT	m_SQL_StmtHandle	= nullptr;
			int			m_StatementID		= 0;
			int			m_QueryStatus		= sql::enm_QueryStatus::NotRunnning;

			//	-------------------------------------------
			//					Variables
			//	-------------------------------------------
			SQL_StatementHandler(int ID)
			{
				this->m_StatementID		= ID;
			}
			~SQL_StatementHandler()
			{

			}
		};

	//	-------------------------------------------
	//				Query Variables
	//	-------------------------------------------
	private:
		SQLHENV									m_SQL_EnvHandle		= nullptr;
		SQLHDBC									m_SQL_Connection	= nullptr;
		SQLRETURN								m_ReturnCode		= 0;
		std::vector<SQL_StatementHandler*>		m_SQL_StmtHandlers;

	//	-------------------------------------------
	//			Threading and concurrency
	//	-------------------------------------------
	private:
		std::mutex		m_SharedMutex;

	//	-------------------------------------------
	//				Variables and flags
	//	-------------------------------------------
	private:
		bool		m_ConnectionSuccess		= false;
		bool		m_ConnectionBusy		= false;
		
	



	//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|
	//						 Public side !
	//	|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|

	//	-------------------------------------------
	//			Constructors and Destructor
	//	-------------------------------------------
	public:
		SQLConnector()
		{

		}

		~SQLConnector()
		{

		}

	//	-------------------------------------------
	//					Functions
	//	-------------------------------------------
	public:
		//	Get the current statement given
		//	by an ID.
		inline SQL_StatementHandler*	GetStatement(	int ID	)
		{
			this->m_SharedMutex.lock();
			//	-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
			for (	int i = 0; 
					i < this->m_SQL_StmtHandlers.size(); 
					++i	)
			{
				if (	this->m_SQL_StmtHandlers[i]->m_StatementID == ID	)
				{
					this->m_SharedMutex.unlock();
					return		this->m_SQL_StmtHandlers[i];
				}
			}
			//	-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
			throw	std::runtime_error("No statement handler was found.");
			this->m_SharedMutex.unlock();	
		}

		//	Add a statement, it just needs and ID.
		inline void			AddStatement(	int ID	)
		{
			//	Now, I am using mutexes. 
			//	I can use also asynchronous emplace back or 
			//	queues, but nah...
			//	Maybe in the future, but I promise 
			//	I'll make this even safer.

			this->m_SharedMutex.lock();
			//	-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
			this->m_SQL_StmtHandlers.push_back(		new SQL_StatementHandler(ID)	);
			//	-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
			this->m_SharedMutex.unlock();
		}

		//	Delete an statement given by
		//	by an statement ID.
		inline void			DeleteStatement(	int ID	)
		{
			this->m_SharedMutex.lock();
			//	-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
			for (	int i = 0; 
					i < this->m_SQL_StmtHandlers.size(); 
					++i	)
			{
				if (	this->m_SQL_StmtHandlers[i]->m_StatementID == ID	)
				{
					//	Freeing the result set from this query.
					SQLFreeStmt(this->m_SQL_StmtHandlers[i]->m_SQL_StmtHandle, SQL_CLOSE);
					//	And also freeing the allocated statement
					SQLFreeHandle(SQL_HANDLE_STMT, this->m_SQL_StmtHandlers[i]->m_SQL_StmtHandle);
					//	Now, proceed to delete safely.
					tls::EraseElement(this->m_SQL_StmtHandlers, i);

					break;
				}
			}
			//	-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
			this->m_SharedMutex.unlock();
		}



		//	This is the function that goes to a thread.
		//	Don't use this function more than once and 
		//	a single thread should manage the connection.
		inline bool			StartConnection(		const std::string& DataBaseDSN		)
		{
			this->m_ConnectionSuccess		= false;



			//	The first step is to allocate the enviroment.
			//	As it says, it is the enviroment. This enviroment (SQLHENV)
			//	will set the base before connecting to a specific database.
			this->m_ReturnCode		= SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &this->m_SQL_EnvHandle);



			//	Set the ODBC version. This function will configure how the game
			//	will interact with the ODBC drivers and the database.
			//	The next step is to allocate the conection to a database.
			this->m_ReturnCode		= SQLSetEnvAttr(this->m_SQL_EnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);



			//	Once the enviroment is all set, now it's time to set a connection.
			//	A connection uses an enviroment so you would be likely to create as 
			//	many connections as you want and a single enviroment.
			this->m_ReturnCode		= SQLAllocHandle(SQL_HANDLE_DBC, this->m_SQL_EnvHandle, &this->m_SQL_Connection);



			//	Just converting the DSN string to SQLCHAR string.
			//	Don't forget about the NTS (Null Terminated String).
			const int		StringSize		= DataBaseDSN.size();
			SQLCHAR*		CharType_DNS	= new SQLCHAR[StringSize + 1];
			{
				for (	int i = 0;
						i < StringSize;
						++i	)
				{
					CharType_DNS[i] = DataBaseDSN[i];
				}

				CharType_DNS[StringSize] = '\0';
			}



			//	As mentioned before, you can create as many connections as you want.
			//	It is useful to connect to one or more databases, threading, more queries, etc.
			//	By the time, I'm only using one single connection.
			this->m_ReturnCode		= SQLConnectA(	this->m_SQL_Connection		,
													CharType_DNS, SQL_NTS		,
													nullptr, 0					,
													nullptr, 0					);



			//	If the retuturn code is not a success value then
			//	manage the exception or error.
			if (	(this->m_ReturnCode == SQL_SUCCESS)				||	
					(this->m_ReturnCode == SQL_SUCCESS_WITH_INFO)	)
			{
				this->m_ConnectionSuccess	= true;
				this->ExecuteQuery(	"USE MyFirstDataBase", -1	);
				this->DeleteStatement(-1);
			}



			//	Deallocate (Free) memory.
			delete[]		CharType_DNS;

			//	Returns true for finished job.
			return		true;
		}

		//	This function will execute any query you provide.
		//	And the DataBaseToUse is just a string parameter.
		//	By the time, I only have one relational data base.
		inline int			ExecuteQuery(	const std::string& QueryString	,
											int QueryID						)
		{
			int		ReturnedQueryStatus = 0;



			//	If no connection was done then don't do a thing
			//	and just keep doing things like normal.
			if (	this->m_ConnectionSuccess	)
			{
				//	Show any possible error or warning.
				//	I can delete this function call since it only
				//	shows the message.
				ShowSQLError(SQL_HANDLE_DBC, this->m_SQL_Connection);



				//	Define a statement handle.
				//	This statement is like instructions
				//	the data base will receive.
				this->AddStatement(QueryID);
				this->GetStatement(QueryID)->m_QueryStatus		= enm_QueryStatus::ErrorWhenAsking;



				//	Allocate a statement handle.
				//	Yes, like SQL Handle Enviroment or Connection, 
				//	the Statement should also be allocated.
				SQLAllocHandle(SQL_HANDLE_STMT, this->m_SQL_Connection, &this->GetStatement(QueryID)->m_SQL_StmtHandle);



				//	Converting the queries and other strings to
				//	valid SQL chars.
				//	Don't forget the Null Terminated String.
				int			StringSize		= QueryString.size();
				SQLCHAR*	SQLCHAR_Query	= new SQLCHAR[StringSize + 1];
				{
					for (	int i = 0;
							i < StringSize;
							++i	)
					{
						SQLCHAR_Query[i] = QueryString[i];
					}
					SQLCHAR_Query[StringSize] = '\0'; 
				}



				//	Execute the SQL Query(ies).
				//	Changing the database will automatically set off the cursor.
				//	So, call the actual query on differents calls.
				this->m_ReturnCode		= SQLExecDirectA(	this->GetStatement(QueryID)->m_SQL_StmtHandle, SQLCHAR_Query, SQL_NTS	);



				//	If the query has been successfully executed,
				//	then set the flag to true and continue
				//	or else just show the error message.
				if (	(this->m_ReturnCode == SQL_SUCCESS)				||
						(this->m_ReturnCode == SQL_SUCCESS_WITH_INFO)	)
				{
					ShowSQLError(	SQL_HANDLE_STMT, this->GetStatement(QueryID)->m_SQL_StmtHandle	);

					this->GetStatement(QueryID)->m_QueryStatus		= enm_QueryStatus::ReadyToPair;
					return		this->GetStatement(QueryID)->m_QueryStatus;
				}
				else
				{
					ShowSQLError(	SQL_HANDLE_STMT, this->GetStatement(QueryID)->m_SQL_StmtHandle	);
					ReturnedQueryStatus		= this->GetStatement(QueryID)->m_QueryStatus;
					this->DeleteStatement(QueryID);
				}



				//	Delete (free) the allocated memory.
				delete[]		SQLCHAR_Query;
			}
			else
			{
				ShowSQLError(	SQL_HANDLE_DBC, this->m_SQL_Connection	);
			}



			return		ReturnedQueryStatus;
		}


		//	Get the string (char, varchar) from a query.
		//	This function will return an empty string if
		//	an error or something else ocurred.
		inline int			GetString(		int WhatColumn, std::string& Str_Ref, int QueryID	)
		{
			//	Initializing values to work with.
			//	By the time, I'm just copying the values 
			//	of the array to the string.
			const int		StringSize = 25;
			SQLCHAR			SQLString[StringSize]{};
			{
				for (	int i = 0;
						i < StringSize;
						++i	)
				{
					SQLString[i] = '\0';
				}
			}



			//	Bindind the column, so when fetching a column the
			//	returned column will be the binded one.
			//	Or rather all the binded columns.
			this->m_ReturnCode		= SQLBindCol(this->GetStatement(QueryID)->m_SQL_StmtHandle, WhatColumn, SQL_C_CHAR, &SQLString, StringSize, nullptr);
			ShowSQLError(SQL_HANDLE_STMT, this->GetStatement(QueryID)->m_SQL_StmtHandle);



			//	Time to fetch.
			//	If the fetching gone wrong then
			//	show the error (what went wrong).
			if (	SQLFetch(this->GetStatement(QueryID)->m_SQL_StmtHandle) == SQL_SUCCESS		)
			{
				for (	int i = 0;
						i < StringSize;
						++i	)
				{
					if (	SQLString[i] != '\0'	)
					{
						Str_Ref.push_back(	SQLString[i]	);
					}
				}
			}
			else
			{
				ShowSQLError(SQL_HANDLE_STMT, this->GetStatement(QueryID)->m_SQL_StmtHandle);
				this->DeleteStatement(QueryID);
				
				return		enm_QueryStatus::ErrorWhenGetting;
			}


			//	Now, deleting may be hard since we are
			//	dealing with thread. But I'm using a kinda
			//	mutex for this job.
			this->DeleteStatement(QueryID);



			//	Return the successful value.
			//	If no fetching was done then
			//	up there return false.
			return		enm_QueryStatus::Done;
		}
		
		//	Get an integer (int) from a query.
		inline int			GetInteger(		int WhatColumn, int* Int_Ref, int QueryID		)
		{
			//	Now, I'm not working with strings,
			//	but integers. So this is the
			//	single declaration to do.
			SQLINTEGER		SQLInteger{};



			//	Bindind the column, so when fetching a column the
			//	returned column will be the binded one.
			//	Or rather all the binded columns.
			this->m_ReturnCode		= SQLBindCol(this->GetStatement(QueryID)->m_SQL_StmtHandle, WhatColumn, SQL_C_LONG, &SQLInteger, sizeof(SQLInteger), nullptr);
			ShowSQLError(SQL_HANDLE_STMT, this->GetStatement(QueryID)->m_SQL_StmtHandle);



			//	Time to fetch.
			//	If the fetching gone wrong then
			//	show the error (what went wrong).
			if (	SQLFetch(this->GetStatement(QueryID)->m_SQL_StmtHandle) == SQL_SUCCESS		)
			{
				//	Just the fetching proccess.
				*Int_Ref		= static_cast<int>(SQLInteger);
			}
			else
			{
				ShowSQLError(SQL_HANDLE_STMT, this->GetStatement(QueryID)->m_SQL_StmtHandle);
				this->DeleteStatement(QueryID);
				
				return		enm_QueryStatus::ErrorWhenGetting;
			}


			//	Deleting the statement.
			this->DeleteStatement(QueryID);

			//	Return the successful value.
			//	If no fetching was done then
			//	up there return false.
			return		enm_QueryStatus::Done;
		}

	//	-------------------------------------------
	//				Setters and Getters
	//	-------------------------------------------
	public:
	};
}