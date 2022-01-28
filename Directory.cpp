
#include "Directory.h"

Dirent::Dirent(std::string arg_name, std::string arg_fhandle)
{
  this->name = arg_name;
  this->fhandle = arg_fhandle;
}

Directory::Directory
(std::string core_arg_host_url, std::string core_arg_owner_vsID,
 std::string core_arg_class_id, std::string core_arg_object_id)
  : Core { core_arg_host_url, core_arg_owner_vsID,
    core_arg_class_id, core_arg_object_id }
{
  std::cout << "a shadow has been created" << std::endl;
}

Directory::Directory
(std::string core_arg_host_url, std::string core_arg_owner_vsID,
 std::string core_arg_class_id, std::string core_arg_object_id,
 std::string arg_name, std::string arg_fhandle)
  : Core { core_arg_host_url, core_arg_owner_vsID,
    core_arg_class_id, core_arg_object_id }
{
  this->dirent_vector_ptr = new std::vector<Dirent *>();
  this->name = arg_name;
  this->fhandle = arg_fhandle;
}

Json::Value
Directory::LookUp
(std::string arg_dir_fhandle, std::string arg_name)
{
  int i;
  int flag = 0;
  Json::Value result;

  if (arg_dir_fhandle == this->fhandle)
    {
      for (i = 0; i < (this->dirent_vector_ptr)->size(); i++)
	{
	  if (((*(this->dirent_vector_ptr))[i])->name == arg_name)
	    {
	      result["fhandle"] = ((*(this->dirent_vector_ptr))[i])->fhandle;
	      flag = 1;
	    }
	}
      if (flag == 0)
	{
	  result["status"] = "NFSERR_NOENT";
	}
      else
	{
	  result["status"] = "NFS_OK";
	}
    }
  else
    {
      result["status"] = "NFSERR_STALE";
    }
  return result;
}

Json::Value
Directory::Create
(std::string arg_dir_fhandle, std::string arg_name, std::string arg_sattr)
{
  int i;
  Json::Value result;

  if (arg_dir_fhandle == this->fhandle)
    {
      int flag = 0;
      for (i = 0; i < (this->dirent_vector_ptr)->size(); i++)
	{
	  if (((*(this->dirent_vector_ptr))[i])->name == arg_name)
	    {
	      flag = 1;
	    }
	}
      if (flag == 0)
	{
	  char fhandle_buf[256];
	  bzero(fhandle_buf, 256);
	  sprintf(fhandle_buf, "%ld%ld", random(), random());
	  std::string new_fhandle { fhandle_buf };

	  Dirent *dirent_ptr = new Dirent(arg_name, new_fhandle);
	  (*(this->dirent_vector_ptr)).push_back(dirent_ptr);
	  result["status"] = "NFS_OK";
	}
      else
	{
	  result["status"] = "NFSERR_ACCES";
	}
    }
  else
    {
      result["status"] = "NFSERR_STALE";
    }
  return result;
}
