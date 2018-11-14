#include "main.h"

namespace notespp {

Main::Main(int argc, char **argv)
{
  result_ = start(argc, argv);
}

Main::~Main()
{
  if (result_ == NOERROR)
    end();
}

STATUS Main::start(int argc, char **argv)
{
  return NotesInitExtended(argc, argv);
}

void Main::end()
{
  NotesTerm();
}

} // namespace notespp
