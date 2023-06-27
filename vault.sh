#!/bin/bash

if [[ $# -ne 1 ]]; then
    echo "Wrong Usage - ./Vault.sh ID"
    exit 0
fi

offset=101357
id="$1"
(( branch_id = id - offset ))

git clone https://github.com/pavel-acsl/hw5a.git
cd hw5a/
git checkout "$branch_id"