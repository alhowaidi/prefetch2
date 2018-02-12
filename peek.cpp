#include "peek.hpp"
#include <string>
#include "ndnpeek.hpp"
#include "core/version.hpp"

#include <ndn-cxx/util/io.hpp>

namespace ndn {
namespace peek {

namespace po = boost::program_options;

static void
usage(std::ostream& os, const po::options_description& options)
{
  os << "Usage: ndnpeek [options] ndn:/name\n"
        "\n"
        "Fetch one data item matching the name prefix and write it to standard output.\n"
        "\n"
     << options;
}

int  ndnChunks::startChunk(std::string ndnName)//, std::string pathName)
//static int
//main(int argc, char* argv[])
{
  PeekOptions options;
  options.isVerbose = false;
  options.mustBeFresh = false;
  options.wantRightmostChild = false;
  options.wantPayloadOnly = false;
  options.minSuffixComponents = -1;
  options.maxSuffixComponents = -1;
  options.interestLifetime = time::milliseconds(-1);
  options.timeout = time::milliseconds(-1);
  
  options.prefix = ndnName;
  Face face;
  NdnPeek program(face, options);

  try {
    program.start();
    face.processEvents(program.getTimeout());
  }
  catch (const std::exception& e) {
    std::cerr << "ERROR: " << e.what() << std::endl;
    return 1;
  }

  ResultCode result = program.getResultCode();
  if (result == ResultCode::TIMEOUT && options.isVerbose) {
    std::cerr << "TIMEOUT" << std::endl;
  }
  return static_cast<int>(result);
}

} // namespace peek
} // namespace ndn

