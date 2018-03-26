<?hh
/*
 *  Copyright (c) 2017-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

namespace HHVM\Packaging;

final class ThirdPartyBinaryNotices {
  public static function getKnownProjects(
  ): dict<string, ?(string, keyset<string>)> {
    return dict[
      'CMakeFiles' => null, // not a project :)
      'brotli' => tuple('Brotli', keyset['brotli/src/LICENSE']),
      'double-conversion' => tuple(
        'double-conversion',
        keyset['double-conversion/LICENSE'],
      ),
      'fastlz' => tuple('FastLZ', keyset['fastlz/src/LICENSE']),
      'fatal' => null, // First-party, i.e. Facebook project
      'folly' => null, // first-party
      'libafdt' => null, // first-party
      'libmbfl' => tuple(
        'Libmbfl',
        keyset[
          'libmbfl/DISCLAIMER',
          'libmbfl/LICENSE',
        ],
      ),
      'libsqlite3' => null, // has a blessing instead of legal notices
      'libzip' => tuple('libzip', keyset['libzip/src/LICENSE']),
      'lz4' => tuple('LZ4', keyset['lz4/src/lib/LICENSE']),
      'mcrouter' => null, // first-party
      'ocaml' => null, // not distributed
      'opam' => null, // not used yet
      'pcre' => tuple('PCRE', keyset['pcre/LICENCE']),
      'proxygen' => null, // first-party
      'ragel' => null, // not distributed
      're2' => tuple('RE2', keyset['re2/src/LICENSE']),
      'squangle' => null, // first-party
      'stubs' => null, // first-party
      'thrift' => null, // first-party
      'timelib' => tuple('Timelib', keyset['timelib/LICENSE.rst']),
      'util' => null, // not distributed
      'wangle' => null, // first-party
      'webscalesqlclient' => tuple(
        'MySQL Client',
        keyset[
          'webscalesqlclient/src/README', // GPL exception
          'webscalesqlclient/src/COPYING',
        ],
      ),
      'zstd' => null, // first-party
    ];
  }

  public static function printNotices(): void {
    print(
      "THE FOLLOWING SETS FORTH ATTRIBUTION NOTICES FOR THIRD PARTY SOFTWARE ".
      "THAT MAY BE CONTAINED IN PORTIONS OF THE FACEBOOK PRODUCT.\n"
    );
    $sentinel = 'DOES_NOT_EXIST';
    $known_projects = self::getKnownProjects();
    $projects = vec[];
    foreach (new \DirectoryIterator(__DIR__.'/../') as $info) {
      if ($info->isDot() || !$info->isDir()) {
        continue;
      }
      $project = $info->getBasename();
      if ($project[0] === '.') {
        continue;
      }
      if (!array_key_exists($project, $known_projects)) {
        fprintf(
          STDERR,
          "Failed to find config for project '%s'\n",
          $project,
        );
        exit(1);
      }
      $projects[] = $project;
    }

    sort(&$projects);
    foreach ($projects as $project) {
      $config = $known_projects[$project] ?? null;
      if ($config === null) {
        continue;
      }
      list($name, $files) = $config;

      print("\n-----\n\n");
      printf(
        "The following software may be included in this product: %s. This ".
        "Software contains the following license and notice below: \n\n",
        $name,
      );
      foreach ($files as $file) {
        $file = __DIR__.'/../'.$file;
        if (!file_exists($file)) {
          fprintf(STDERR, "%s does not exist\n", $file);
          exit(2);
        }
        print(file_get_contents($file));
      }
    }
  }
}

ThirdPartyBinaryNotices::printNotices();
