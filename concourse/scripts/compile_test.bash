#!/bin/bash -l

set -eox pipefail

CWDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
source "${CWDIR}/common.bash"

function gen_env(){
  cat > /opt/run_test.sh <<-EOF
		trap look4diffs ERR

		function look4diffs() {

		    diff_files=\`find .. -name regression.diffs\`

		    for diff_file in \${diff_files}; do
			if [ -f "\${diff_file}" ]; then
			    cat <<-FEOF

						======================================================================
						DIFF FILE: \${diff_file}
						----------------------------------------------------------------------

						\$(cat "\${diff_file}")

					FEOF
			fi
		    done
		    exit 1
		}
		source /usr/local/greenplum-db-devel/greenplum_path.sh
		if [ -f /opt/gcc_env.sh ]; then
		    source /opt/gcc_env.sh
		fi
		cd "\${1}/filedump_src"
		source ../gpdb_src/gpAux/gpdemo/gpdemo-env.sh
		make -s ${MAKE_DOWNLOAD_COMMAND}
		make -s ${MAKE_COMPILE_COMMAND}
		make -s ${MAKE_TEST_COMMAND}
	EOF

	chmod a+x /opt/run_test.sh
}

function setup_gpadmin_user() {
    ./gpdb_src/concourse/scripts/setup_gpadmin_user.bash "$TEST_OS"
}

function _main() {
    if [ -z "${MAKE_TEST_COMMAND}" ]; then
        echo "FATAL: MAKE_TEST_COMMAND is not set"
        exit 1
    fi

    if [ -z "$TEST_OS" ]; then
        echo "FATAL: TEST_OS is not set"
        exit 1
    fi

    case "${TEST_OS}" in
    centos|ubuntu|sles) ;; #Valid
    *)
      echo "FATAL: TEST_OS is set to an invalid value: $TEST_OS"
      echo "Configure TEST_OS to be centos, or ubuntu"
      exit 1
      ;;
    esac

	yum install -y openssh-server openssh-clients
    time install_and_configure_gpdb
    time setup_gpadmin_user
	chown gpadmin:gpadmin filedump_src
    time make_cluster
    time gen_env
    time run_test
}

_main "$@"
