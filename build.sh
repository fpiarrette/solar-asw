#!/bin/sh

# obtain project base dir
script_dir=$(readlink -f $(pwd)/$(dirname "$0"))
project_dir=$script_dir

# reset getopts
OPTIND=1

# initialize varaibles
flags="-t"
cmd="make clean all"

# create source dir
workspace_dir="/ws"

source_dir=/src

# create output dir
output_dir=/build

# default platform
platform_xt_atto_lxl=xt_atto_lxl
platform_host=host
platform="${platform_xt_atto_lxl}"

optimization=0

debug=0

show_help()
{
    echo "$0 [-i] [-s {/src}] [-o {/build}] [-p {$platform_xt_atto_lxl/$platform_host}] [-c {\"make clean all\"}] [-z] [-d] [-h]"
}

while getopts "h?is:o:c:p:zd" opt; do
  case "$opt" in
    h|\?)
      show_help
      exit 0
      ;;
    i)
      flags="${flags} -i"
      cmd="bash"
      ;;
    s)
      source_dir="${OPTARG}"
      ;;
    o)
      output_dir="${OPTARG}"
      ;;
    c)
      cmd="${OPTARG}"
      ;;
    p)
      platform="${OPTARG}"
      ;;
    z)
      optimization=1
      ;;
    d)
      debug=1
      ;;
  esac
done

shift $((OPTIND-1))

[ "${1:-}" = "--" ] && shift

# info
echo "--------------------------------------------------------------------------------"
echo "Solar build system"
#echo "Source: ${project_dir}${source_dir}"
#echo "Output: ${project_dir}${output_dir}"
echo "Command: ${cmd}"
echo "Platform: ${platform}"
echo "--------------------------------------------------------------------------------"

if [ "$platform" != "$platform_xt_atto_lxl" ] && [ "$platform" != "$platform_host" ]
then
  show_help
  exit 0
fi

# create output dir just in case make clean is not executed
mkdir -p ${project_dir}${output_dir}

if [ "$platform" = "$platform_xt_atto_lxl" ]
then
  # launch make process
  podman run ${flags} \
    -v "${project_dir}:/ws" \
    -w "${workspace_dir}" \
    -e "SRC=${workspace_dir}${source_dir}" \
    -e "OUTPUT=${workspace_dir}${output_dir}" \
    -e "PLATFORM=${platform}" \
    -e "DEBUG=${debug}" \
    -e "OPTIMIZATION=${optimization}" \
    arm-poky-linux-gnueabi:latest \
    ${cmd}
elif [ "$platform" = "$platform_host" ]
then
  SRC="${project_dir}${source_dir}" OUTPUT="${project_dir}${output_dir}" PLATFORM="${platform}" DEBUG="${debug}" OPTIMIZATION="${optimization}" ${cmd}

fi

